#include "../../minishell.h"
#include <string.h>

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
		g_global.ret_val = cd(commands);
}

char	**dup_env(char **envp)
{
	char	**env;
	int	i;

	i = 0;
	while (envp[i])
		i++;
	env = (char **)malloc((i + 1) * sizeof(char *));
	if (!env)
		error_msg("Error malloc envp");
	i = -1;
	while (envp[++i])
	{
		env[i] = strdup(envp[i]);
		if (!env[i])
			error_msg("Error strdup envp");
	}
	env[i] = NULL;
	return (env);
}
