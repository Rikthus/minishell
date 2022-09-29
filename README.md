## Recreate a very basic shell (WIP)

### A faire:

- expansion des variables d'env **DONE**
- trim quotes **PARTIALLY DONE**
- redirections et exec (expansion du "$?")
- gestion des signaux **PARTIALLY DONE** (see blocking cmd: grep and cat)
- gestion de l'historique **DONE**
- built-ins et makefile gcc builtins avec dependance minishell.h



### BUGS:

- bad quotes trimming **PARTIALLY DONE**

- gestion si pas de commande **DONE**
- check if cmd in token and if ENV VARIABLE EXISTS AND IF PATH exists    else only do redir  **DONE**
- if ./minishell inside minishell bad ctrl-C
- bad signal Maxine <3 Maxine <3 if ctrl-c after cat
- heredoc




- parsing: si pas d'envp alors env_list->env_var = NULL (et juste un element dans env_list)



**TESTS**
- while true; do leaks minishell; sleep 1.6; clear; done (test leaks during exec)
- env -i ./minishell (check minishell with no env)
- cat /dev/urandom ./minishell
- < /dev/urandom ./minishell
