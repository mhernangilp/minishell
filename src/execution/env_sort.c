/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:56:39 by mhernang          #+#    #+#             */
/*   Updated: 2023/12/21 19:07:52 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void sort_list(char ***s_env);
static void	print_declare(char **s_env);

void	env_sorted(t_bridge *bridge)
{
	char	**s_env;

	s_env = dup_env(bridge -> m_env);
	sort_list(&s_env);
	print_declare(s_env);
	free_env(&s_env);
}
