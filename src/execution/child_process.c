/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:50:22 by mhernang          #+#    #+#             */
/*   Updated: 2023/11/12 20:52:56 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

static char	*get_command(char **paths, char *file);

void	child_process(t_exec exec, int num)
{
	char	*command;

	set_redirections(&exec, num);
	close_all(&exec);
	command = get_command(exec.paths, exec.bridge->commands[num][0]);
	if (is_builtin(exec.bridge -> commands[num][0]))
	{
		builtins(exec.bridge -> commands[num], CHILD);
		exit(get_ret_val());
	}
	if (!command)
		error_msg(exec.bridge->commands[num][0], 127);
	else if (execve(command, exec.bridge->commands[num], g_env))
		error_msg("Error execution", 1);
}

static char	*get_command(char **paths, char *file)
{
	char	*command;
	char	*temp;

	if (!ft_strncmp("./", file, 2))
	{
		if (access(file, F_OK | X_OK) == 0)
			return (file);
		ft_putstr_fd("minishell: ", 2);
		error_msg(file, 126);
	}
	if (paths)
	{
		while (*paths)
		{
			temp = ft_strjoin(*paths, "/");
			command = ft_strjoin(temp, file);
			free(temp);
			if (access(command, F_OK | X_OK) == 0)
				return (command);
			free(command);
			paths++;
		}
	}
	return (NULL);
}
