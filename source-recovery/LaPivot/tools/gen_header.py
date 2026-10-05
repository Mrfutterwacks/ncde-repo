#!/usr/bin/env python3
"""gen_header.py <Class> — emit the public interface of <Class> from interfaces/LaPivot-metaobjects.h
(Qt's own moc metadata dumped from the oracle), as a C++ class body fragment: Q_PROPERTYs with
READ = property name, signals, public/private slots and Q_INVOKABLEs, in metadata order.
Members and hand-written helpers are added around it by hand."""
import re, sys, pathlib
cls = sys.argv[1]
src = (pathlib.Path(__file__).parent.parent / 'interfaces' / 'LaPivot-metaobjects.h').read_text()
body = re.search(r'^class %s .*?^};' % re.escape(cls), src, re.S | re.M).group(0)
props, getters, sigs, slots, inv = [], [], [], {'public': [], 'private': [], 'protected': []}, []
for line in body.splitlines():
    line = line.strip()
    m = re.match(r'Q_PROPERTY\((.+?) (\w+) READ \?( WRITE \?)?( NOTIFY (\w+))?( CONSTANT)?( FINAL)?\)', line)
    if m:
        t, n, w, _, notify, const, _ = m.groups()
        s = f'    Q_PROPERTY({t} {n} READ {n}'
        if w: s += f' WRITE set{n[0].upper()}{n[1:]}'
        if notify: s += f' NOTIFY {notify}'
        if const: s += ' CONSTANT'
        props.append(s + ')')
        getters.append(f'    {t} {n}() const;')
        if w: getters.append(f'    void set{n[0].upper()}{n[1:]}({t} v);')
        continue
    m = re.match(r'(signal:|slot:|Q_INVOKABLE)\s+(public|private|protected)\s+(.+?)\s+(\w+)\((.*)\);', line)
    if m:
        kind, acc, ret, name, params = m.groups()
        decl = f'    {ret} {name}({params});'
        if kind == 'signal:': sigs.append(decl)
        elif kind == 'slot:': slots[acc].append(decl)
        else: inv.append(f'    Q_INVOKABLE {ret} {name}({params});')
PRIM = {'bool','int','uint','uchar','double','qlonglong','qulonglong','float','qint64','quint64'}
def cref(params):
    out = []
    for p in [x.strip() for x in params.split(',') if x.strip()]:
        parts = p.rsplit(' ', 1)
        t, n = (parts[0], parts[1]) if len(parts) == 2 and not parts[1].endswith('>') and parts[0] else (p, '')
        if t in PRIM or t.endswith('*'):
            out.append(p)
        else:
            out.append(f'const {t} &{n}'.rstrip(' &') + ('' if n else ' &'))
    return ', '.join(out)
# moc emits a default-argument clone as a second, shorter entry: fold it into a default.
# Defaults come from DEFAULTS (read from the oracle's qt_static_metacall).
DEFAULTS = {('Lelan', 'setAutoLogin'): 'true'}
def fold(decls):
    res, byname = [], {}
    for d in decls:
        name = re.search(r'(\w+)\(', d).group(1)
        byname.setdefault(name, []).append(d)
    for d in decls:
        name = re.search(r'(\w+)\(', d).group(1)
        group = byname[name]
        if len(group) > 1 and (cls, name) in DEFAULTS:
            longest = max(group, key=len)
            if d != longest: continue
            d = d[:-2] + f' = {DEFAULTS[(cls, name)]});'
        res.append(d)
    return res
sigs = [re.sub(r'\((.*)\)', lambda m: '(' + cref(m.group(1)) + ')', d) for d in sigs]
for acc in slots:
    slots[acc] = fold([re.sub(r'\((.*)\)', lambda m: '(' + cref(m.group(1)) + ')', d) for d in slots[acc]])
inv = [re.sub(r'\((.*)\)', lambda m: '(' + cref(m.group(1)) + ')', d) for d in inv]
out = ['    Q_OBJECT'] + props + ['', 'public:'] + getters + [''] + inv + ['', 'signals:'] + sigs
for acc in ('public', 'protected', 'private'):
    if slots[acc]: out += ['', f'{acc} slots:'] + slots[acc]
print('\n'.join(out))
