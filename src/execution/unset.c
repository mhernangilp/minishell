/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:37:53 by mhernang          #+#    #+#             */
/*   Updated: 2023/12/19 15:47:33 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	unset(t_bridge *bridge, char **commands)
{
	int	i;

	i = 0;
	while (commands[++i])
		b_delete(&bridge -> m_env, commands[i]);
	return (0);
}

void	b_delete(char ***m_env, char *key)
{
	char	**new_env;
	int		i;
	int		j;

	if (!getenv_value(*m_env, key))
		return ;
	new_env = (char **)malloc(env_len(*m_env) * sizeof(char *));
	if (!new_env)
		exit_msg(ERR_MEMORY, 1);
	i = -1;
	j = 0;
	while ((*m_env)[++i])
	{
		if (!(!ft_strncmp(key, (*m_env)[i], ft_strlen(key))
			&& (*m_env)[i][ft_strlen(key)] == '='))
		{
			new_env[j] = ft_strdup((*m_env)[i]);
			j++;
		}
	}
	new_env[j] = NULL;
	free_env(*m_env);
	*m_env = new_env;
}
