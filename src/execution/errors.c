/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:41:02 by mhernang          #+#    #+#             */
/*   Updated: 2023/10/15 13:57:15 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_msg(char *msg, int val)
{
	perror(msg);
	exit (val);
}

void	exit_msg(char *msg, int val)
{
	ft_putstr_fd(msg, 2);
	exit (val);
}
