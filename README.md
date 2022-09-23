### A faire:

- expansion des variables d'env
- trim quotes
- redirections et exec (expansion du "$?")
- gestion des signaux
**DONE**- gestion de l'historique
- built-ins



### BUGS:

**DONE**- **Segfault if free(token->redir)**
- (optional : checker si le terminal est un tty valid)
**DONE**- (optional : $"lol")
- echo "lol"okep => lolokep (they are the same element)
 (the current shell treat "lol" and okep as separated elements)





**TEST LEAKS**
while true; do leaks minishell; sleep 1.6; clear; done
