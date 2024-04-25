# Minishell

42SP 8th common-core project, minishell is a shell that aims to reproduce most of bash's behaviors.

## Installation and usage
```c
git clone git@github.com:iuryr/minishell.git minishell
cd minishell
make
./minishell
```

dependency: GNU readline library (https://directory.fsf.org/wiki/Readline#tab=Overview)

## Features
- Input redirection: `cat < file.txt`)
- Here-documents: `cat << eof`, then input as many lines as you want. End input with a line containing 'eof' (the delimiter we set earlier) or CTRL+D;
- Output redirection: `echo arg1 arg2 > output.txt` and `echo arg3 >> output.txt`
- Pipelines: `cat Makefile | grep CC | wc -l`
- Environment Variables: `export VAR=value`
- Working prompt history
- Bashes exit status: echo $?
- Signal handling similar to bash
- The following builtins: echo, cd, pwd, export, unset, env, exit
- Double quotes preserves variable expansion, single quotes prevent variable expansion.
