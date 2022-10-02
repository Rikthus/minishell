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
1. Finish 2 builtins
2. BUILTIN PIPES et check fd leaks
3. HEREDOC signals ctrl-d new line to remove and segfault with multiple heredocs and signals
4. Make error messages and good g_exit_status update
5. Fix quotes with redir inside and multiple env var replacing
6. Test Builtins
7. Norm everything
8. Crash Test Everything

**BUILTINS_ERRORS**
- pwd : DONE
- env : almost DONE
- unset : segfault if unsetting first env variable

**TESTS**
- while true; do leaks minishell; sleep 1.6; clear; done (test leaks during exec)
- env -i ./minishell (check minishell with no env)
- cat /dev/urandom ./minishell
- < /dev/urandom ./minishell
- lsof -p <PID process> (fuite de fd)
