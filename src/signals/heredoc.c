/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:15:19 by gfernand          #+#    #+#             */
/*   Updated: 2023/11/13 16:24:00 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	sig_handler_heredoc(int signal)
{
	(void) signal;
	//ft_store_result_code(1, true);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

void	heredoc_signals(void)
{
	signal(SIGINT, sig_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
