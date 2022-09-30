## Recreate a very basic shell (WIP)

### A faire:

- expansion des variables d'env **DONE**
- trim quotes **PARTIALLY DONE**
- redirections et exec (expansion du "$?")
- gestion des signaux **PARTIALLY DONE** (see blocking cmd: grep and cat)
- gestion de l'historique **DONE**
- built-ins et makefile gcc builtins avec dependance minishell.h
- SIGNAUX .....


### BUGS:

- bad quotes trimming **PARTIALLY DONE**

- gestion si pas de commande **DONE**
- check if cmd in token and if ENV VARIABLE EXISTS AND IF PATH exists    else only do redir  **DONE**
- if ./minishell inside minishell bad ctrl-C
- bad signal Maxine <3 Maxine <3 if ctrl-c after cat
- heredoc




- parsing: si pas d'envp alors env_list->env_var = NULL (et juste un element dans env_list)

## TO DO
- line with only spaces **DONE**

**SIGNALS**
- ctrl-\ in a prompt after you wrote some stuff : should quit minishell  **SEE BASH**
- heredoc BAD CTRL-D

**QUOTES**
- bad redir handling **!!!!!!!!!!!WARNING!!!!!!!!!!!!!**
- check echo "dsfdsf $" (env var) PB and echo "$hjghg$jh  YNU$jnb$njhb" and
- bad malloc with echo "dsfkhsdf <><><>><dh <>"

**HISTORY**
- pb  **DONE** pb not replicable

## FINALISATION
1. Add builtins in exec
2. Finish 2 builtins
3. Fix Heredox signals
4. Fix fd leak 1 pipe sur HEREDOC (test avec signaux)
5. Make error messages and good g_exit_status update
6. Fix quotes with redir inside and multiple env var replacing
7. Test Builtins
8. Norm everything
9. Crash Test Everything

**TESTS**
- while true; do leaks minishell; sleep 1.6; clear; done (test leaks during exec)
- env -i ./minishell (check minishell with no env)
- cat /dev/urandom ./minishell
- < /dev/urandom ./minishell
- lsof -p <PID process> (fuite de fd)

Charline, rajoute la gestion des builtins de la meme maniere que tu geres les commandes mais en dehors du fork, tout en gardant les redirections et les pipes. Attention a close() le bon nombre de pipes et a ne pas wait() les executions de builtins car ce ne sont pas des binaires (donc juste wait les processus qui s'executent dans des fork() avec execve() ).
