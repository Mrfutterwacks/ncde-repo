#!/usr/bin/env bash
# Verda Teminae shell integration — source this from ~/.bashrc
# Source: /usr/local/share/ncde-terminal/shell-integration/verda.bash

__verda_precmd() {
    printf '\033]133;D\007'                              # output end
    printf '\033]7;file://%s%s\007' "$HOSTNAME" "$PWD"  # working dir
    printf '\033]133;A\007'                              # prompt start
}
__verda_postprompt() {
    printf '\033]133;B\007'                              # command start
}
__verda_preexec() {
    printf '\033]133;C\007'                              # output start
}

if [[ -z "$VERDA_SHELL_INTEGRATION" ]]; then
    export VERDA_SHELL_INTEGRATION=1
    PROMPT_COMMAND="__verda_precmd${PROMPT_COMMAND:+;$PROMPT_COMMAND}"
    PS1="${PS1}$(printf '\033]133;B\007')"   # initial command start
    command -v verdafetch >/dev/null 2>&1 && verdafetch
fi
