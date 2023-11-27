/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:30:26 by gfernand          #+#    #+#             */
/*   Updated: 2023/11/13 16:35:46 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	sig_handler_process(int signal)
{
	(void) signal;
	printf("Quit: 3\n");
	rl_redisplay();
}
static void	sig_handler_int(int signal)
{
	(void) signal;
	printf("\n");
	rl_redisplay();
}

void	process_signals(void)
{
	signal(SIGINT, sig_handler_int);
	signal(SIGQUIT, sig_handler_process);
}
