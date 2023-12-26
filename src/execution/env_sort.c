/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:56:39 by mhernang          #+#    #+#             */
/*   Updated: 2023/12/26 12:43:38 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void sort_list(char **s_env);
static void	print_declare(char **s_env);

void	env_sorted(t_bridge *bridge)
{
	char	**s_env;

	s_env = dup_env(bridge -> m_env);
	if (s_env && s_env[0] && s_env[1])
	{
		sort_list(s_env);
		print_declare(s_env);
	}
	free_env(s_env);
}

static void	print_declare(char **s_env)
{
	int	i;

	i = -1;
	while (s_env[++i])
	{
		if (ft_strncmp("?=", s_env[i], 2))
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(s_env[i], 1);
			ft_putchar_fd('\n', 1);
		}
	}
}

static void sort_list(char **s_env)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	while (++i < env_len(s_env) - 1)
	{
		j = 0;
        while (s_env[j + 1])
		{
            if (ft_strncmp(s_env[j], s_env[j + 1], ft_strlen(s_env[j])) > 0)
			{
                temp = s_env[j];
				s_env[j] = s_env[j + 1];
				s_env[j + 1] = temp;
            }
			j++;
        }
    }
}
