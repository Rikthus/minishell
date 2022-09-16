### A faire:

- expansion des variables d'env
- redirections et exec (expansion du "$?")
- gestion des signaux
- gestion de l'historique
- built-ins



### BUGS:

- **Segfault if free(token->redir)**
- (optional : checker si le terminal est un tty valid)
- (optional : $"lol")