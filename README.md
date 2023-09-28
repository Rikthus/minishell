# Recreate a minimalistic shell

### (Deprecated version but still usable)

 *Project made for MACOS

Current big bugs:
 - if launched without environnement executed child process will segfault
 - if the path is deleted builtin commands are not usable
 - bad handling of the '-n' flag for echo command

**TESTS**
- while true; do leaks minishell; sleep 1.6; clear; done (test leaks during exec)
- env -i ./minishell (check minishell with no env)
- cat /dev/urandom ./minishell
- < /dev/urandom ./minishell
- lsof -p <PID process> (fd leaks)
