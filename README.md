## Recreate a very basic shell (WIP)

## TO DO

**SIGNALS**
- heredoc BAD CTRL-D

**HISTORY**

## FINALISATION
1. Make error messages and good g_exit_status update **Almost**
2. Norm everything
3. Test Builtins **Almost**
4. Crash Test Everything
5. (optional) HEREDOC signals ctrl-d new line to remove

**BUILTINS_ERRORS**

**ERRORS**
- if removing path and try to execute commands **DONE**
- message when trying to use an unknown command **DONE**
- heredoc on cmd 3 or more if piped cmds **DONE**
- sefault when heredoc in first or second cmd and heredocs in 3rd or more cmd **DONE**
- after multiple pipes redir on outfile doesn't work **DONE**

**TESTS**
- while true; do leaks minishell; sleep 1.6; clear; done (test leaks during exec)
- env -i ./minishell (check minishell with no env)
- cat /dev/urandom ./minishell
- < /dev/urandom ./minishell
- lsof -p <PID process> (fuite de fd)
