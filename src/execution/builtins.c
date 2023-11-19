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

void	builtins(char **commands)
{
	if (!strcmp(commands[0], "cd"))
		cd(commands);
	if (!strcmp(commands[0], "pwd"))
		pwd();
	if (!strcmp(commands[0], "env"))
		env();
	if (!strcmp(commands[0], "unset"))
		unset(commands);
	if (!strcmp(commands[0], "export"))
		b_export(commands);
	if (!strcmp(commands[0], "echo"))
		echo(commands);
	if (!strcmp(commands[0], "exit"))
		b_exit(commands);
}
