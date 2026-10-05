// ncde-recovery-hotkey.c — standalone Ctrl+Alt+R global hotkey grabber for NCDE Soundings recovery.
//
// Root-caused 2026-09-23: LaPivot (the WM) has NO native X11 key grab anywhere in the binary
// (confirmed: zero xcb_grab_key/XGrabKey symbols) and its QML Keys.onPressed shortcut only ever
// fires when LaPivot's own window holds X11 input focus — which it hands off to whatever app is
// active (xcb_set_input_focus), so the shortcut silently does nothing during real desktop use.
// The real fix is a native passive key grab. Rather than route this through a from-scratch
// reconstruction + recompile of NCDEWindowManager (73-method, zero-groundwork Tier-2 hub class,
// the single production WM binary with no fallback tree — far too large a blast radius for one
// hotkey), this is a small standalone companion process: X11 allows any client to hold a passive
// grab on a key combo nothing else has grabbed, so this needs zero changes to LaPivot itself.
//
// On match: launches the exact same command already proven working (NOPASSWD sudoers scoped to
// this one binary, confirmed live 2026-09-23): sudo -n /usr/local/bin/ncde-recovery

#include <xcb/xcb.h>
#include <xcb/xcb_keysyms.h>
#include <X11/keysym.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>

// Modifier-lock variants X11 passive grabs require: a grab is matched by EXACT modifier state,
// so NumLock/CapsLock/ScrollLock being on must each be grabbed separately or the shortcut
// silently stops firing whenever a lock key happens to be on.
static const uint16_t LOCK_MASKS[] = { 0, XCB_MOD_MASK_LOCK, XCB_MOD_MASK_2,
                                        XCB_MOD_MASK_LOCK | XCB_MOD_MASK_2 };
#define NUM_LOCK_VARIANTS (sizeof(LOCK_MASKS) / sizeof(LOCK_MASKS[0]))
#define BASE_MODS (XCB_MOD_MASK_CONTROL | XCB_MOD_MASK_1)

static void launch_recovery(void) {
    pid_t pid = fork();
    if (pid == 0) {
        setsid();
        execlp("sudo", "sudo", "-n", "/usr/local/bin/ncde-recovery", (char *)NULL);
        _exit(127);
    } else if (pid > 0) {
        signal(SIGCHLD, SIG_IGN);
    }
}

int main(void) {
    int screen_num;
    xcb_connection_t *conn = xcb_connect(NULL, &screen_num);
    if (xcb_connection_has_error(conn)) {
        fprintf(stderr, "ncde-recovery-hotkey: cannot connect to X display\n");
        return 1;
    }

    const xcb_setup_t *setup = xcb_get_setup(conn);
    xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);
    for (int i = 0; i < screen_num; i++) xcb_screen_next(&iter);
    xcb_window_t root = iter.data->root;

    xcb_key_symbols_t *syms = xcb_key_symbols_alloc(conn);
    if (!syms) {
        fprintf(stderr, "ncde-recovery-hotkey: xcb_key_symbols_alloc failed\n");
        return 1;
    }
    xcb_keycode_t *keycodes = xcb_key_symbols_get_keycode(syms, XK_r);
    if (!keycodes || keycodes[0] == XCB_NO_SYMBOL) {
        fprintf(stderr, "ncde-recovery-hotkey: no keycode for XK_r\n");
        return 1;
    }
    xcb_keycode_t keycode = keycodes[0];
    free(keycodes);

    for (size_t i = 0; i < NUM_LOCK_VARIANTS; i++) {
        xcb_grab_key(conn, 1, root, BASE_MODS | LOCK_MASKS[i], keycode,
                     XCB_GRAB_MODE_ASYNC, XCB_GRAB_MODE_ASYNC);
    }
    xcb_flush(conn);

    xcb_generic_event_t *ev;
    while ((ev = xcb_wait_for_event(conn))) {
        if ((ev->response_type & ~0x80) == XCB_KEY_PRESS) {
            xcb_key_press_event_t *kp = (xcb_key_press_event_t *)ev;
            if (kp->detail == keycode && (kp->state & BASE_MODS) == BASE_MODS) {
                launch_recovery();
            }
        }
        free(ev);
    }

    xcb_key_symbols_free(syms);
    xcb_disconnect(conn);
    return 0;
}
