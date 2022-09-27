## Recreate a very basic shell (WIP)

### A faire:

- expansion des variables d'env **DONE**
- trim quotes **PARTIALLY DONE**
- redirections et exec (expansion du "$?")
- gestion des signaux **PARTIALLY DONE** (see blocking cmd: grep and cat)
- gestion de l'historique **DONE**
- built-ins



### BUGS:

- **Segfault if free(token->redir)** **DONE**
- (optional : checker si le terminal est un tty valid) **DONE**
- (optional : $"lol") **DONE**
- echo "lol"okep => lolokep (they are the same element)
 (the current shell treat "lol" and okep as separated elements) **DONE**
- bad quotes trimming **PARTIALLY DONE**

- BUG : PIPE NON SUIVI D'UNE COMMANDE **DONE**

- < a pb
- > a pb
- check if cmd in token and if ENV VARIABLE EXISTS AND IF PATH exists    else only do redir 
- if ./minishell inside minishell bad ctrl-C

- parsing: si pas d'envp alors env_list->env_var = NULL (et juste un element dans env_list)



**TEST LEAKS**
- while true; do leaks minishell; sleep 1.6; clear; done
