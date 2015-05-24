#ifndef __LAUNCHER_H__
#define __LAUNCHER_H__


void launch_process(Process *proc, char **argv, int terminal);

int is_builtin_command(Cmd *command);
int launch_command(Cmd *command, Shell *shell);
int launch_builtin_command(Cmd *command, Shell *shell);


// __LAUNCHER_H__
#endif
