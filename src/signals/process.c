/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:30:26 by gfernand          #+#    #+#             */
/*   Updated: 2023/12/04 16:08:48 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	sig_handler_process(int signal)
{
	(void) signal;
	printf("Quit: 3\n");
	rl_redisplay();
	add("?=131", RETVAL);
}

static void	sig_handler_int(int signal)
{
	(void) signal;
	printf("\n");
	rl_redisplay();
	add("?=130", RETVAL);
}

void	process_signals(void)
{
	signal(SIGINT, sig_handler_int);
	signal(SIGQUIT, sig_handler_process);
}
