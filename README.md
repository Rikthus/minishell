### A faire:

- expansion des variables d'env
- redirections et exec (expansion du "$?")
- gestion des signaux
- gestion de l'historique
- built-ins



### BUGS:

**DONE**- **Segfault if free(token->redir)**
- (optional : checker si le terminal est un tty valid)
**DONE**- (optional : $"lol")





**TEST LEAKS**
while true; do leaks minishell; sleep 1.6; clear; done
