/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:17:09 by mhernang          #+#    #+#             */
/*   Updated: 2023/10/15 13:56:56 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	initialize_exec(t_exec *exec, t_bridge *bridge)
{
	int	i;

	  printf("Allocating memory for %d pipes\n", bridge -> ncommands - 1);
	exec -> pipe = malloc((bridge -> ncommands - 1) * sizeof(int *));
	if (!(exec -> pipe))
		error_msg("Error allocating memory\n");
	i = -1;
	while (++i < (bridge -> ncommands - 1))
	{
		exec -> pipe[i] = malloc(2 * sizeof(int));
		if (!(exec -> pipe[i]))
			error_msg("Error allocating memory\n");
		if (pipe(exec -> pipe[i]) < 0)
			error_msg("Error creating pipe\n");
	}
	  printf("Allocating memory for %d pids\n", bridge -> ncommands);
	exec -> pid = malloc((bridge -> ncommands) * sizeof(pid_t));
	if (!(exec -> pid))
		error_msg("Error allocating memory\n");
	exec -> bridge = bridge;
}

void	execution(t_bridge *bridge)
{
	t_exec	exec;

	initialize_exec(&exec, bridge);
}
