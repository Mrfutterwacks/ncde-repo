#!/usr/bin/env python3
# step21-overrides.py — the metadata half of step21-rootless-refresh.sh (2026-10-01).
#   step21-overrides.py <image-tree> <canonical-src> <work>            -> work/pseudo.txt + work/excludes.txt
#   step21-overrides.py --verify <image-tree> <canonical-src> <work>   -> checks work/airootfs.sfs against them
#   step21-overrides.py --shot <qmp.sock> <out.png>                    -> QEMU screenshot over QMP
#
# Every file the image needs changed is EXCLUDED from the root-owned tree and re-added as a mksquashfs pseudo
# definition carrying exact content + owner + mode + mtime. Nothing is guessed: unreadable files are only
# taken from a source proven identical (size + mtime against the tree's own stat), or rebuilt and size-checked.
import base64, json, os, re, shlex, socket, stat, subprocess, sys, time

def esc(name):        # pseudo-definition / exclude file names: backslash-escape specials
    return re.sub(r'([\\ "*?\[\]])', r'\\\1', name)

def perm_bits(s):     # '-rwsr-x--T' -> 0o4750 | ...
    m = 0
    for i, (r, w, x) in enumerate(((1, 2, 3), (4, 5, 6), (7, 8, 9))):
        sh = 6 - 3 * i
        if s[r] == 'r': m |= 4 << sh
        if s[w] == 'w': m |= 2 << sh
        if s[x] in 'xst': m |= 1 << sh
    if s[3] in 'sS': m |= 0o4000
    if s[6] in 'sS': m |= 0o2000
    if s[9] in 'tT': m |= 0o1000
    return m

def parse_listing(path):
    """unsquashfs -lln -> {relpath: (type, mode, uid, gid, size, mtime, linktarget)}"""
    out = {}
    rx = re.compile(r'^(\S{10})\s+(\d+)/(\d+)\s+(\S+)\s+(\d{4}-\d\d-\d\d \d\d:\d\d)\s+squashfs-root(/.*?)?(?: -> (.*))?$')
    for line in open(path, errors='surrogateescape'):
        m = rx.match(line.rstrip('\n'))
        if not m: continue
        p = (m.group(6) or '/').lstrip('/')
        size = m.group(4)
        out[p] = (m.group(1)[0], perm_bits(m.group(1)), int(m.group(2)), int(m.group(3)),
                  int(size) if size.isdigit() else size,
                  int(time.mktime(time.strptime(m.group(5), '%Y-%m-%d %H:%M'))), m.group(7))
    return out

def same_minute(a, b): return int(a) // 60 == int(b) // 60

class Plan:
    def __init__(s): s.entries = {}; s.excl = set(); s.xattr = {}; s.notes = []
    def F(s, p, src, mtime, mode, uid, gid): s.entries[p] = ('F', int(mtime), mode & 0o7777, uid, gid, src)
    def D(s, p, mtime, mode, uid, gid): s.entries[p] = ('D', int(mtime), mode & 0o7777, uid, gid, None)
    def S(s, p, target, mtime, uid=0, gid=0): s.entries[p] = ('S', int(mtime), 0o777, uid, gid, target)
    def X(s, p): s.excl.add(p)

def build(A, SRC, B):
    pl = Plan(); now = int(time.time())
    T = lambda p: os.lstat(os.path.join(A, p))
    old = parse_listing(os.path.join(B, 'old-sfs-list.txt'))
    fails = []

    # ── 1. files/dirs the user cannot read ───────────────────────────────────────────────────────────────
    for line in open(os.path.join(B, 'unreadable.txt')):
        t, p = line.rstrip('\n').split('\t', 1)
        st = T(p); meta = (st.st_mtime, st.st_mode, st.st_uid, st.st_gid)
        pl.X(p)
        if p.startswith('var/cache/pacman/pkg/download-'):
            continue                                               # pacman's aborted temp dir: never ship
        if p in ('boot/initramfs-linux.img', 'boot/initramfs-linux-zen.img'):
            pl.F(p, os.path.join(B, 'initramfs', os.path.basename(p)), *meta); continue
        if p == 'var/cache/ldconfig':
            pl.D(p, *meta); continue                               # aux-cache: ldconfig rebuilds it
        if t == 'f':
            ov = os.path.join(B, 'ov', p)
            if p in ('etc/shadow', 'etc/gshadow'):
                if os.path.getsize(ov) != st.st_size: fails.append(p + ': rebuilt size differs')
                pl.F(p, ov, *meta); continue
            if p in ('etc/shadow-', 'etc/gshadow-'):              # the pre-upgrade copies = the July files
                src = os.path.join(B, 'oldx', p[:-1])
                if os.path.getsize(src) != st.st_size: fails.append(p + ': backup size differs')
                pl.F(p, src, *meta); continue
            if os.path.exists(ov):
                o = os.stat(ov)
                if o.st_size != st.st_size or not same_minute(o.st_mtime, st.st_mtime):
                    fails.append(p + ': package copy differs from tree'); continue
                pl.F(p, ov, *meta); continue
            src = os.path.join(B, 'oldx', p); ol = old.get(p)
            if not os.path.exists(src) or not ol or ol[4] != st.st_size or not same_minute(ol[5], st.st_mtime):
                fails.append(p + ': no proven source'); continue
            pl.F(p, src, *meta); continue
        if t == 'd':
            base = os.path.join(B, 'oldx', p)
            if not os.path.isdir(base): fails.append(p + ': dir missing from July image'); continue
            pl.D(p, *meta)
            ol = old.get(p)
            if not ol or not same_minute(ol[5], st.st_mtime):
                pl.notes.append('dir changed since July, July contents used: ' + p)
            for root, dirs, files in os.walk(base):
                for n in dirs + files:
                    full = os.path.join(root, n); rel = os.path.relpath(full, os.path.join(B, 'oldx'))
                    o = old.get(rel)
                    if not o: fails.append(rel + ': not in July listing'); continue
                    ty, mode, uid, gid, size, mt, link = o
                    if ty == 'd': pl.D(rel, mt, mode, uid, gid)
                    elif ty == '-': pl.F(rel, full, mt, mode, uid, gid)
                    elif ty == 'l': pl.S(rel, link, mt, uid, gid)
                    else: pl.notes.append('skipped %s (type %s, runtime leftover)' % (rel, ty))
            continue
        fails.append(p + ': unhandled type ' + t)

    # ── 2. NCDE: the canonical tree where it differs from the image (same filter as step20 'ncde') ─────────
    skip = re.compile(r'(__pycache__|\.pyc$|prebak|\.reverted-|\.retired-|\.README\.md$|^home/|^flutter-backgrounds/|'
                      r'^usr/share/ncde/controls/_a11y_test\.qml$|^etc/geoclue/conf\.d/90-ncde-static\.conf$|'
                      r'^etc/ncde/hummingbird-google-client\.json$)')
    ncde = 0
    for root, dirs, files in os.walk(SRC):
        for n in files:
            full = os.path.join(root, n); rel = os.path.relpath(full, SRC)
            if skip.search(rel) or os.path.islink(full): continue
            dests = [(rel, 0, 0)]
            if rel.startswith('etc/skel/'): dests.append(('home/live/' + rel[len('etc/skel/'):], 1000, 1000))
            sst = os.stat(full)
            for d, uid, gid in dests:
                # The live session's wallpaper must name the LIVE user's own Pictures dir. skel carries the
                # operator's dev path (July shipped that too) and mirroring it verbatim painted the desktop
                # black on the ISO, because /home/stephen does not exist there. July's own home/live copy
                # pointed at /home/live; chrooted_post_install.sh rewrites this per-user on install anyway.
                src = full
                if d == 'home/live/.config/ncde/wallpaper.conf':
                    src = os.path.join(B, 'home-live-wallpaper.conf')
                    if not os.path.exists(src):
                        fails.append(d + ': no live wallpaper source'); continue
                tp = os.path.join(A, d)
                if os.path.lexists(tp):
                    try:
                        if open(tp, 'rb').read() == open(src, 'rb').read() and \
                           (os.lstat(tp).st_mode & 0o7777) == (sst.st_mode & 0o7777): continue
                    except PermissionError: pass
                    pl.X(d)
                pl.F(d, src, sst.st_mtime, sst.st_mode, uid, gid); ncde += 1
    # ── 2b. Boost 1.91.0 alongside 1.92.0 — the installer needs it ────────────────────────────────────────
    # /usr/bin/calamares is a vendored binary owned by no package, so the 09-29 upgrade replaced Boost
    # (1.91.0 -> 1.92.0) and left the May-11 binary linked against the old soname. `pkexec calamares -d`
    # then died with exit=127 ("libboost_python314.so.1.91.0: cannot open shared object file") and the
    # installer never appeared, although ncde-x11-session fired launch.sh correctly every time. These are
    # the three libraries July shipped, recovered from old.sfs and verified against it by size + mtime.
    boost = os.path.join(B, 'boostx', 'usr', 'lib')
    for n in sorted(os.listdir(boost)) if os.path.isdir(boost) else []:
        if not n.endswith('.so.1.91.0'): continue
        f = os.path.join(boost, n); stt = os.stat(f)
        ol = old.get('usr/lib/' + n)
        if not ol or ol[4] != stt.st_size or not same_minute(ol[5], stt.st_mtime):
            fails.append('usr/lib/' + n + ': does not match the July copy'); continue
        pl.F('usr/lib/' + n, f, stt.st_mtime, stt.st_mode, 0, 0); ncde += 1

    cap = os.getxattr(os.path.join(A, 'usr/local/bin/LaPivot'), 'security.capability')
    pl.xattr['usr/local/bin/LaPivot'] = 'security.capability=0s' + base64.b64encode(cap).decode()

    # ── 3. NCDE repo preinstalled: package files + pacman DB entries ─────────────────────────────────────
    for pk in ('ncde', 'qpa'):
        base = os.path.join(B, 'pkgx', pk)
        for root, dirs, files in os.walk(base):
            for n in files + [d for d in dirs if os.path.islink(os.path.join(root, d))]:
                full = os.path.join(root, n); rel = os.path.relpath(full, base)
                if rel.startswith('.'): continue
                st = os.lstat(full)
                if os.path.lexists(os.path.join(A, rel)): pl.X(rel)
                if os.path.islink(full): pl.S(rel, os.readlink(full), st.st_mtime)
                else: pl.F(rel, full, st.st_mtime, st.st_mode, 0, 0)
    local = os.path.join(B, 'pdb/root/var/lib/pacman/local')
    for d in sorted(os.listdir(local)):
        if not d.startswith('ncde'): continue
        rel = 'var/lib/pacman/local/' + d; pl.D(rel, now, 0o755, 0, 0)
        for f in sorted(os.listdir(os.path.join(local, d))):
            pl.F(rel + '/' + f, os.path.join(local, d, f), now, 0o644, 0, 0)
    for rel in ('etc/pacman.conf', 'usr/bin/chrooted_post_install.sh'):
        st = T(rel); pl.X(rel); pl.F(rel, os.path.join(B, 'ov', rel), now, st.st_mode, st.st_uid, st.st_gid)
    pl.F('usr/local/share/ncde-fix/ncde-repo.gpg', os.path.join(B, 'ov/usr/local/share/ncde-fix/ncde-repo.gpg'), now, 0o644, 0, 0)

    # ── 4. retired / removed (as on the live machine) ────────────────────────────────────────────────────
    pl.S('etc/systemd/user/ncde-automount.service', '/dev/null', now)        # patch 7l: global mask
    # Vesper must never launch on an install medium OR on an installed system (operator, 2026-10-02 —
    # it opened over the running installer, and must not start on a fresh install either). Both the
    # live session and skel ship vesper-brain.service in default.target.wants; mask both so no new
    # user inherits it. pl.X first: mksquashfs only applies a symlink pseudo definition where the tree
    # has NO entry of that name — verified this session, where masks aimed at pre-existing symlinks
    # were silently discarded while verify-sfs still reported PASSED.
    for _v, _o in (('home/live/.config/systemd/user/default.target.wants/vesper-brain.service', (1000, 1000)),
                   ('etc/skel/.config/systemd/user/default.target.wants/vesper-brain.service', (0, 0))):
        pl.X(_v)
        pl.S(_v, '/dev/null', now, *_o)
    pl.X('etc/geoclue/conf.d/90-ncde-static.conf')                            # patch item 33
    pl.X('usr/local/share/ncde-fix/ncde-full-patch-20260711.sh')               # July patch: would DOWNGRADE; current one ships in usr/lib/ncde-update
    ob = [d for d in os.listdir(os.path.join(A, 'var/lib/pacman/local')) if d.startswith('openbox-')]
    for d in ob:
        pl.X('var/lib/pacman/local/' + d)
        lines = open(os.path.join(A, 'var/lib/pacman/local', d, 'files')).read().split('%FILES%\n', 1)[1].split('\n\n')[0]
        for f in lines.splitlines():
            if not f.endswith('/') or 'openbox' in f.lower(): pl.X(f.rstrip('/'))

    # ── write ────────────────────────────────────────────────────────────────────────────────────────────
    with open(os.path.join(B, 'pseudo.txt'), 'w') as o:
        for p in sorted(pl.entries):
            k, mt, mode, uid, gid, x = pl.entries[p]
            if k == 'F': o.write('%s F %d %o %d %d cat %s\n' % (esc(p), mt, mode, uid, gid, shlex.quote(x)))
            elif k == 'D': o.write('%s D %d %o %d %d\n' % (esc(p), mt, mode, uid, gid))
            else: o.write('%s S %d %o %d %d %s\n' % (esc(p), mt, mode, uid, gid, x))
        for p, v in sorted(pl.xattr.items()): o.write('%s x %s\n' % (esc(p), v))
    step20 = ['proc/*', 'sys/*', 'dev/*', 'run/*', 'tmp/*', 'mnt/*', 'var/cache/ncde/qmlcache/*',
              'helpwithisla', 'calamares-ncde', 'wallpapers', 'compass7', 'src', 'build', 'ncde-wm', 'version',
              'etc/calamares/branding/archcraft', 'var/lib/pacman/sync/archcraft.db', 'etc/arch-release',
              '... *.prebak*', '... *.tmp', '... *.rebuilt-broken-*', '... *.restored-from-*', '... *.wrong-*',
              '... *.bak', '... *.orig', '... *.swp', '... *.brokenhtml-*', '... __pycache__', '... *.iso-aside-*',
              'usr/bin/ollama', 'usr/share/ollama', 'usr/lib/ollama', 'usr/share/licenses/ollama', 'var/lib/ollama',
              'var/lib/pacman/local/ollama-*', 'opt/ncde-chroma', 'usr/local/bin/kickass-guard',
              'usr/local/lib/ncde/ncde-vesper-provision.sh', 'usr/lib/systemd/system/ollama.service',
              'usr/lib/systemd/system/chroma.service', 'usr/lib/systemd/system/kickass-guard.service',
              'usr/lib/systemd/system/ncde-vesper-provision.service', 'usr/lib/tmpfiles.d/ncde-kickass.conf',
              'usr/lib/sysusers.d/ollama.conf', 'usr/lib/tmpfiles.d/ollama.conf', 'usr/share/factory/etc/arch-release',
              'usr/share/dbus-1/services/org.ncde.KickassGuard.service',
              'usr/local/share/dbus-1/services/org.ncde.KickassGuard.service', 'usr/lib/systemd/user/ncde-sentinel.service',
              'usr/bin/ncde-terminal', 'usr/local/bin/ncde-tauri-installer', 'usr/share/ncde/GliaDocPopup.',
              'usr/share/ncde/MagpieTalker', 'usr/share/ncde/NCDESettings', 'usr/share/ncde/SpacePanel.qm',
              'CLAUDE.md', 'PROJECT.md', 'NCDE-CALAMARES-PLAN.md', 'NCDE-INSTALL-PLAN.md', 'ISO-BUILD-PLAN.md',
              'SESSION_HANDOFF.md', 'preview.html', 'check_session.sh', 'complete_checklist.sh', 'install_hooks.sh',
              'log_command.sh', 'require_search_for_uncertainty.sh', 'settings.json', '... deploy-*.sh', '... revert-*.sh']
    with open(os.path.join(B, 'excludes.txt'), 'w') as o:
        for p in sorted(pl.excl): o.write(esc(p) + '\n')
        for p in step20: o.write(p + '\n')
    json.dump({'entries': {p: list(v[:5]) + [os.path.getsize(v[5]) if v[0] == 'F' else None] for p, v in pl.entries.items()}, 'excl': sorted(pl.excl),
               'xattr': pl.xattr}, open(os.path.join(B, 'plan.json'), 'w'))
    for n in pl.notes: print('note:', n)
    for f in fails: print('FAIL:', f)
    print('NCDE files from canonical: %d' % ncde)
    print('pseudo definitions: %d, excluded tree paths: %d, openbox packages removed: %s' % (len(pl.entries), len(pl.excl), ob))
    if fails: sys.exit(1)

def verify(A, SRC, B):
    plan = json.load(open(os.path.join(B, 'plan.json')))
    subprocess.run(['unsquashfs', '-lln', os.path.join(B, 'airootfs.sfs')], stdout=open(os.path.join(B, 'new-sfs-list.txt'), 'w'),
                   stderr=subprocess.DEVNULL)
    new = parse_listing(os.path.join(B, 'new-sfs-list.txt')); bad = 0
    for p, (k, mt, mode, uid, gid, size) in plan['entries'].items():
        n = new.get(p)
        if k == 'F' and n and n[4] != size: print('BAD size', p, n[4], 'want', size); bad += 1
        want = {'F': '-', 'D': 'd', 'S': 'l'}[k]
        if not n or n[0] != want or (k != 'S' and (n[1] != mode or n[2] != uid or n[3] != gid)):
            print('BAD override', p, n); bad += 1
    gone = [p for p in plan['excl'] if p in new and p not in plan['entries']]
    for p in gone: print('BAD still present', p); bad += 1
    for pat in ('.prebak', '.iso-aside-', 'openbox.desktop', '90-ncde-static.conf', 'var/cache/pacman/pkg/download-'):
        hit = [p for p in new if pat in p]
        if hit: print('BAD leaked', pat, hit[:3]); bad += 1
    # suid/sgid: every one in the tree must keep its bits (except excluded paths)
    tree = subprocess.run(['find', A, '-xdev', '-perm', '/6000', '-printf', '%P\\n'], capture_output=True, text=True).stdout.split()
    for p in tree:
        if p in plan['excl'] and p not in plan['entries']: continue
        n = new.get(p); st = os.lstat(os.path.join(A, p))
        if not n or n[1] != (st.st_mode & 0o7777) or n[2] != st.st_uid or n[3] != st.st_gid:
            print('BAD suid/sgid', p, n); bad += 1
    hl = new.get('home/live')
    if not hl or hl[2:4] != (1000, 1000): print('BAD home/live owner', hl); bad += 1
    lp = new.get('usr/local/bin/LaPivot')
    lpsha = subprocess.run('sqfscat %s usr/local/bin/LaPivot | sha256sum' % shlex.quote(os.path.join(B, 'airootfs.sfs')),
                           shell=True, capture_output=True, text=True).stdout[:16]
    srcsha = subprocess.run(['sha256sum', os.path.join(SRC, 'usr/local/bin/LaPivot')], capture_output=True, text=True).stdout[:16]
    if lpsha != srcsha: print('BAD LaPivot in image', lpsha, 'want', srcsha); bad += 1
    # file capabilities: every security.capability in the tree (+ LaPivot) must be in the image
    # (extracted under `unshare -r`: in a user namespace with CAP_SETFCAP unsquashfs may set file caps on our files)
    caps = {}
    for l in subprocess.run(['getcap', '-r', A], capture_output=True, text=True).stdout.splitlines():
        f, c = l.rsplit(' ', 1); caps[os.path.relpath(f, A)] = c
    caps['usr/local/bin/LaPivot'] = 'cap_sys_nice=ep'
    want = [p for p in caps if not (p in plan['excl'] and p not in plan['entries'])]
    cx = os.path.join(B, 'capcheck'); subprocess.run(['chmod', '-R', 'u+w', cx], stderr=subprocess.DEVNULL); subprocess.run(['rm', '-rf', cx])
    open(os.path.join(B, 'capfiles.txt'), 'w').write('\n'.join(want) + '\n')
    subprocess.run(['unshare', '-r', 'unsquashfs', '-d', cx, '-ef', os.path.join(B, 'capfiles.txt'), os.path.join(B, 'airootfs.sfs')],
                   stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    got = {}
    for l in subprocess.run(['getcap', '-r', cx], capture_output=True, text=True).stdout.splitlines():
        f, c = l.rsplit(' ', 1); got[os.path.relpath(f, cx)] = c
    for p in want:
        if got.get(p) != caps[p]: print('BAD capability', p, 'image', got.get(p), 'want', caps[p]); bad += 1
    print('file capabilities checked:', len(want))
    print('suid/sgid checked: %d, overrides checked: %d, image entries: %d, LaPivot %s' % (len(tree), len(plan['entries']), len(new), lpsha))
    print('VERIFY', 'PASSED' if bad == 0 else 'FAILED (%d)' % bad)
    sys.exit(1 if bad else 0)

def shot(sock, png):
    s = socket.socket(socket.AF_UNIX); s.connect(sock); f = s.makefile('rw')
    f.readline()
    for cmd in ({'execute': 'qmp_capabilities'}, {'execute': 'screendump', 'arguments': {'filename': png, 'format': 'png'}}):
        f.write(json.dumps(cmd) + '\n'); f.flush(); print(f.readline().strip())

if __name__ == '__main__':
    if sys.argv[1] == '--verify': verify(*sys.argv[2:5])
    elif sys.argv[1] == '--shot': shot(*sys.argv[2:4])
    else: build(*sys.argv[1:4])
