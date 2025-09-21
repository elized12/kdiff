    #!/bin/bash

    _kdiff_completion() {
        local curr options
        curr="${COMP_WORDS[COMP_CWORD]}"
        options="--ignore-symbol= --ranges --count-diff= --case-sensitive"
        
        if [[ ${curr} == -* ]]; then
            COMPREPLY=( $(compgen -W "${options}" -- "${curr}") )
        else
            COMPREPLY=( $(compgen -f -- "${curr}") )
        fi
        
        return 0
    }

    complete -F _kdiff_completion kdiff