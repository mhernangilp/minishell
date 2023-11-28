/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:37:08 by mhernang          #+#    #+#             */
/*   Updated: 2023/11/26 18:37:10 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	finish(int ret, int type);
static int	is_zero(char *str);

int	b_exit(char **commands, int type)
{
	if (!commands[1])
		finish(0, type);
	if (!commands[2])
	{
		if (ft_atoi(commands[1]) > 0 || is_zero(commands[1]))
			finish(ft_atoi(commands[1]), type);
		if (ft_atoi(commands[1]) < 0 || ft_atoi(commands[1]) > 255)
			finish((ft_atoi(commands[1]) % 256 + 256) % 256,
				type);
		if (type == PARENT)
			ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(commands[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit (2);
	}
	if (type == PARENT)
		ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	return (1);
}

static void	finish(int ret, int type)
{
	if (type == PARENT)
		ft_putstr_fd("exit\n", 2);
	exit (ret);
}

static int	is_zero(char *str)
{
	int	i;

	if (!*str)
		return (0);
	i = -1;
	while (str[++i])
		if (str[i] != '0')
			return (0);
	return (1);
}
