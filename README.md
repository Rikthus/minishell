## Recreate a very basic shell (WIP)

## FINALISATION
1. (optional) HEREDOC signals ctrl-d new line to remove

**TESTS**
- while true; do leaks minishell; sleep 1.6; clear; done (test leaks during exec)
- env -i ./minishell (check minishell with no env)
- cat /dev/urandom ./minishell
- < /dev/urandom ./minishell
- lsof -p <PID process> (fuite de fd)
