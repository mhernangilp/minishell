/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 20:43:51 by mhernang          #+#    #+#             */
/*   Updated: 2023/11/30 12:49:38 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pwd(void)
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, PATH_MAX))
		return (1);
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
