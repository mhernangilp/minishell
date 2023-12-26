/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_ctrl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:59:31 by gfernand          #+#    #+#             */
/*   Updated: 2023/12/26 14:59:34 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ctr(void)
{
	int				x;
	struct termios	termios;

	x = tcgetattr(0, &termios);
	if (x)
	{
		perror("");
		exit(1);
	}
	termios.c_lflag &= ~ECHOCTL;
	x = tcsetattr(0, 0, &termios);
	if (x)
	{
		perror("");
		exit(1);
	}
}
