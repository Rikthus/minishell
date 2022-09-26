## Recreate a very basic shell (WIP)

### A faire:

- expansion des variables d'env **DONE**
- trim quotes **PARTIALLY DONE**
- redirections et exec (expansion du "$?")
- gestion des signaux
- gestion de l'historique **DONE**
- built-ins



### BUGS:

- **Segfault if free(token->redir)** **DONE**
- (optional : checker si le terminal est un tty valid) **DONE**
- (optional : $"lol") **DONE**
- echo "lol"okep => lolokep (they are the same element)
 (the current shell treat "lol" and okep as separated elements) **DONE**
- bad quotes trimming **PARTIALLY DONE**





**TEST LEAKS**
- while true; do leaks minishell; sleep 1.6; clear; done
