/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:17:09 by mhernang          #+#    #+#             */
/*   Updated: 2023/11/12 20:43:33 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	wait_all(t_exec *exec);
static char	**get_paths();
static void	initialize_exec(t_exec *exec, t_bridge *bridge);

void	execution(t_bridge *bridge)
{
	t_exec	exec;
	int		i;

	initialize_exec(&exec, bridge);
	exec.paths = get_paths();
	if (bridge -> n_cmds == 1 && is_parent_builtin(bridge -> commands[0][0]))
		builtins(bridge -> commands[0], PARENT);
	else
	{
		i = -1;
		while (++i < exec.bridge -> n_cmds)
		{
			exec.pid[i] = fork();
			if (exec.pid[i] == 0)
					child_process(exec, i);
		}
		close_all(&exec);
		wait_all(&exec);
	}
}

void	close_all(t_exec *exec)
{
	int	i;

	i = -1;
	while (++i < (exec -> bridge -> n_cmds - 1))
	{
		close(exec -> pipe[i][0]);
		close(exec -> pipe[i][1]);
	}
}

static void	wait_all(t_exec *exec)
{
	int	i;

	i = -1;
	while (++i < (exec -> bridge -> n_cmds))
		waitpid(exec -> pid[i], NULL, 0);
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

	exec -> pipe = malloc((bridge -> n_cmds - 1) * sizeof(int *));
	if (!(exec -> pipe))
		error_msg("Error allocating memory\n");
	i = -1;
	while (++i < (bridge -> n_cmds - 1))
	{
		exec -> pipe[i] = malloc(2 * sizeof(int));
		if (!(exec -> pipe[i]))
			error_msg("Error allocating memory\n");
		if (pipe(exec -> pipe[i]) < 0)
			error_msg("Error creating pipe\n");
	}
	exec -> pid = malloc((bridge -> n_cmds) * sizeof(pid_t));
	if (!(exec -> pid))
		error_msg("Error allocating memory\n");
	exec -> bridge = bridge;
	exec -> in_out = malloc(bridge -> n_cmds * sizeof(int *));
	if (!(exec -> in_out))
		error_msg("Error allocating memory\n");
	i = -1;
	while (++i < (bridge -> n_cmds))
	{
		exec -> in_out[i] = malloc(2 * sizeof(int));
		if (!(exec -> in_out[i]))
			error_msg("Error allocating memory\n");
		exec -> in_out[i][0] = -1;
		exec -> in_out[i][1] = -1;
	}
}
