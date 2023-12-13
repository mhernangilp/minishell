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
	g_signal = 3;
}

static void	sig_handler_int(int signal)
{
	(void) signal;
	printf("\n");
	rl_redisplay();
	g_signal = 2;
}

void	process_signals(char **m_env)
{
	signal(SIGINT, sig_handler_int);
	signal(SIGQUIT, sig_handler_process);
	if (g_signal == 3)
	{
		printf("SEÑAAAAAAAALLL\n");
		set_ret_val(m_env, 131);
	}
	else if (g_signal == 2)
		set_ret_val(m_env, 130);
}
