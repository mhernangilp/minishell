/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:36:33 by mhernang          #+#    #+#             */
/*   Updated: 2023/11/26 18:36:45 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_n(char *str);

int	echo(char **commands)
{
	int	start;

	if (!commands[1])
	{	
		write(1, "\n", 1);
		return (0);
	}
	start = 0;
	if (is_n(commands[1]))
		start = 1;
	while (commands[++start])
	{
		ft_putstr_fd(commands[start], 1);
		if (commands[start + 1])
			write(1, " ", 1);
	}
	if (ft_strncmp(commands[1], "-n", 2))
		write(1, "\n", 1);
	return (0);
}

static int	is_n(char *str)
{
	int	i;

	if (!*str || *str != '-')
		return (0);
	i = 0;
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	return (1);
}
