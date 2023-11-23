#include "../../minishell.h"
#include <string.h>

int	is_parent_builtin(char *command)
{
	if (!strcmp(command, "cd"))
		return (1);
	if (!strcmp(command, "export"))
		return (1);
	if (!strcmp(command, "unset"))
		return (1);
	if (!strcmp(command, "exit"))
		return (1);
	return (0);
}

int	is_builtin(char *command)
{
	if (!strcmp(command, "echo"))
		return (1);
	if (!strcmp(command, "cd"))
		return (1);
	if (!strcmp(command, "pwd"))
		return (1);
	if (!strcmp(command, "export"))
		return (1);
	if (!strcmp(command, "unset"))
		return (1);
	if (!strcmp(command, "env"))
		return (1);
	if (!strcmp(command, "exit"))
		return (1);
	return (0);
}

void	builtins(char **commands, int type)
{
	if (!strcmp(commands[0], "cd"))
		set_ret_val(cd(commands));
	if (!strcmp(commands[0], "pwd"))
		set_ret_val(pwd());
	if (!strcmp(commands[0], "env"))
		set_ret_val(env());
	if (!strcmp(commands[0], "unset"))
		set_ret_val(unset(commands));
	if (!strcmp(commands[0], "export"))
		set_ret_val(b_export(commands));
	if (!strcmp(commands[0], "echo"))
		set_ret_val(echo(commands));
	if (!strcmp(commands[0], "exit"))
		set_ret_val(b_exit(commands, type));
}
