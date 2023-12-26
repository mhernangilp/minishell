/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:11:36 by mhernang          #+#    #+#             */
/*   Updated: 2023/11/30 16:17:47 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_heredoc(t_exec *exec, t_bdg *bridge)
{
	int	i;

	exec -> here = malloc(bridge -> n_cmds * sizeof(t_here));
	i = -1;
	while (++i < (bridge -> n_cmds))
	{
		exec -> here[i].count = count_heredocs(bridge -> redirect[i].inred);
		if (exec -> here[i].count)
			if (pipe(exec -> here[i].here_pipe) < 0)
				error_msg("ERR_PIPES", 1);
	}
}

void	init_in_out(t_exec *exec, t_bdg *bridge)
{
	int	i;

	exec -> in_out = malloc(bridge -> n_cmds * sizeof(int *));
	if (!(exec -> in_out))
		exit_msg(ERR_MEMORY, 1);
	i = -1;
	while (++i < (bridge -> n_cmds))
	{
		exec -> in_out[i] = malloc(2 * sizeof(int));
		if (!(exec -> in_out[i]))
			exit_msg(ERR_MEMORY, 1);
		exec -> in_out[i][0] = -1;
		exec -> in_out[i][1] = -1;
	}
}
