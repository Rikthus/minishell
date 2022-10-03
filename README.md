## Recreate a very basic shell (WIP)

## TO DO

**SIGNALS**
- heredoc BAD CTRL-D

**HISTORY**

## FINALISATION
1. Finish 1 builtins
2. Make error messages and good g_exit_status update
4. Norm everything
3. Test Builtins
5. Crash Test Everything
6. (optional) HEREDOC signals ctrl-d new line to remove

**BUILTINS_ERRORS**

**TESTS**
- while true; do leaks minishell; sleep 1.6; clear; done (test leaks during exec)
- env -i ./minishell (check minishell with no env)
- cat /dev/urandom ./minishell
- < /dev/urandom ./minishell
- lsof -p <PID process> (fuite de fd)
