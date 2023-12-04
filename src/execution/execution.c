/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:17:09 by mhernang          #+#    #+#             */
/*   Updated: 2023/11/30 16:16:42 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	wait_all(t_exec *exec);
static char	**get_paths(void);
static void	initialize_exec(t_exec *exec, t_bridge *bridge);

void	execution(t_bridge *bridge)
{
	t_exec	exec;
	int		i;

	initialize_exec(&exec, bridge);
	exec.paths = get_paths();
	load_heredoc(&exec);
	if (bridge -> n_cmds == 1 && bridge -> commands[0][0]
		&& is_parent_builtin(bridge -> commands[0][0]))
		builtins(bridge -> commands[0], PARENT);
	else
	{
		i = -1;
		while (++i < exec.bridge -> n_cmds)
		{
			exec.pid[i] = fork();
			if (!bridge->redirect[i].inred)
				process_signals();
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
	int	ret_val;

	i = -1;
	while (++i < (exec -> bridge -> n_cmds))
		waitpid(exec -> pid[i], &ret_val, 0);
	if (WIFEXITED(ret_val))
		set_ret_val(WEXITSTATUS(ret_val));
	else
		if (ft_atoi(getenv_value("?")) != 130
			&& ft_atoi(getenv_value("?")) != 131)
			set_ret_val(255);
}

static char	**get_paths(void)
{
	char	*path;
	char	**paths;

	path = getenv_value("PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		exit_msg(ERR_MEMORY, 1);
	return (paths);
}

static void	initialize_exec(t_exec *exec, t_bridge *bridge)
{
	int	i;

	exec -> pipe = malloc((bridge -> n_cmds - 1) * sizeof(int *));
	if (!(exec -> pipe))
		exit_msg(ERR_MEMORY, 1);
	i = -1;
	while (++i < (bridge -> n_cmds - 1))
	{
		exec -> pipe[i] = malloc(2 * sizeof(int));
		if (!(exec -> pipe[i]))
			exit_msg(ERR_MEMORY, 1);
		if (pipe(exec -> pipe[i]) < 0)
			error_msg("ERR_PIPES", 1);
	}
	exec -> pid = malloc((bridge -> n_cmds) * sizeof(pid_t));
	if (!(exec -> pid))
		exit_msg(ERR_MEMORY, 1);
	exec -> bridge = bridge;
	init_in_out(exec, bridge);
	init_heredoc(exec, bridge);
}
