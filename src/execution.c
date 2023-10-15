/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:17:09 by mhernang          #+#    #+#             */
/*   Updated: 2023/10/15 17:24:34 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_all(t_exec *exec)
{
	int	i;

	i = -1;
	while (++i < (exec -> bridge -> ncommands - 1))
	{
		close(exec -> pipe[i][0]);
		close(exec -> pipe[i][1]);
	}
}

static char	**get_paths()
{
	char	*path;
	char	**paths;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		error_msg("Error searching PATH");
	return (paths);
}

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
	exec -> in = -1;
	exec -> out = -1;
}

static void	wait_all(t_exec *exec)
{
	int	i;

	i = -1;
	while (++i < (exec -> bridge -> ncommands))
		waitpid(exec -> pid[i], NULL, 0);
}

void	execution(t_bridge *bridge)
{
	t_exec	exec;
	int		i;

	initialize_exec(&exec, bridge);
	exec.paths = get_paths();
	i = -1;
	while (++i < exec.bridge -> ncommands)
	{
		exec.pid[i] = fork();
		if (exec.pid[i] == 0)
				child_process(exec, i);
	}
	close_all(&exec);
	wait_all(&exec);
}
