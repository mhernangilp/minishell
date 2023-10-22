/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:50:22 by mhernang          #+#    #+#             */
/*   Updated: 2023/10/22 17:50:49 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_command(char **paths, char *file);

void	child_process(t_exec exec, int num)
{
	char	*command;

	set_redirections(&exec, num);
	close_all(&exec);
	command = get_command(exec.paths, exec.bridge->commands[num][0]);
	if (!command)
		error_msg("Error with command");
	if (execve(command, exec.bridge->commands[num], exec.envp))
		error_msg("Error executing");
}

static char	*get_command(char **paths, char *file)
{
	char	*command;
	char	*temp;

	if (access(file, F_OK | X_OK) == 0)
		return (file);
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
