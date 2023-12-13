/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_val.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:37:40 by mhernang          #+#    #+#             */
/*   Updated: 2023/11/26 18:37:41 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	set_ret_val(char **m_env, int val)
{
	char	*new_env;
	char	*value;

	value = ft_itoa(val);
	new_env = ft_strjoin("?=", value);
	add(m_env, new_env, RETVAL);
	free(value);
	free(new_env);
}

int	get_ret_val(char **m_env)
{
	int	i;

	i = 0;
	while (m_env[i] && m_env[i][0] != '?')
		i++;
	return (ft_atoi(m_env[i] + 2));
}
