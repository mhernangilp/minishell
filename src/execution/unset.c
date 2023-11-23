#include "../../minishell.h"

int	unset(char **commands)
{
	int	i;

	i = 0;
	while (commands[++i])
		b_delete(commands[i]);
	return (0);
}

void	b_delete(char *key)
{
	char	**new_env;
	int	i;
	int	j;

	if (!getenv_value(key))
		return ;
	new_env = (char **)malloc(env_len(g_env) * sizeof(char *));
	if (!new_env)
		error_msg(ERR_MEMORY, 1);
	i = -1;
	j = 0;
	while (g_env[++i])
	{
		if (!(!ft_strncmp(key, g_env[i], ft_strlen(key))
			&& g_env[i][ft_strlen(key)] == '='))
		{
			new_env[j] = ft_strdup(g_env[i]);
			j++;
		}
	}
	new_env[j] = NULL;
	free_env(g_env);
	g_env = new_env;
}
