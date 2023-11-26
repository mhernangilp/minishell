/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:36:50 by mhernang          #+#    #+#             */
/*   Updated: 2023/11/26 18:36:54 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	env()
{
	int	i;

	i = -1;
	while (g_env[++i])
		ft_putstr_fd(g_env[i], 1);
	return (0);
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
		error_msg(ERR_MEMORY, 1);
	i = -1;
	while (envp[++i])
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
			error_msg(ERR_MEMORY, 1);
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
