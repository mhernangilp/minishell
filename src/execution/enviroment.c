
#include "../../minishell.h"

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
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
			error_msg("Error strdup envp");
	}
	env[i] = NULL;
	return (env);
}

char	*getenv_value(char *key)
{
	int	i;

	i = -1;
	while (g_env[++i])
	{
		if (!ft_strncmp(key, g_env[i], ft_strlen(key))
			&& g_env[i][ft_strlen(key)] == '=')
			return (g_env[i] + ft_strlen(key) + 1);
	}
	return (NULL);
}

int	env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	free_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		free(env[i]);
	free(env);
}
