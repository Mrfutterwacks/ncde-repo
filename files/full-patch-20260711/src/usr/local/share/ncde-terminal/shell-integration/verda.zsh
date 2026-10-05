#!/usr/bin/env zsh
# Verda Teminae shell integration — source this from ~/.zshrc
# Source: /usr/local/share/ncde-terminal/shell-integration/verda.zsh

__verda_precmd() {
    print -n '\033]133;D\007'
    print -n "\033]7;file://$HOST$PWD\007"
    print -n '\033]133;A\007'
}
__verda_preexec() {
    print -n '\033]133;C\007'
}

if [[ -z "$VERDA_SHELL_INTEGRATION" ]]; then
    export VERDA_SHELL_INTEGRATION=1
    precmd_functions+=(__verda_precmd)
    preexec_functions+=(__verda_preexec)
    print -n '\033]133;B\007'
    command -v verdafetch >/dev/null 2>&1 && verdafetch
fi
