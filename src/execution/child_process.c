/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:50:22 by mhernang          #+#    #+#             */
/*   Updated: 2023/11/30 16:31:08 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <dirent.h>

static char	*get_command(char **paths, char *file);
static char	*has_paths(char **paths, char *file);
static int	is_here(char *file);
static void	check_directories(char *file);

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
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(exec.bridge->commands[num][0], 2);
		exit_msg(": command not found\n", 127);
	}
	else if (execve(command, exec.bridge->commands[num], g_env))
		error_msg("Error execution", 1);
}

static char	*get_command(char **paths, char *file)
{
	char	*command;

	check_directories(file);
	if (!ft_strncmp("/", file, 1))
	{
		if (access(file, F_OK | X_OK) == 0)
			return (file);
		ft_putstr_fd("minishell: ", 2);
		error_msg(file, 126);
	}
	if (paths)
	{
		printf("Si\n");
		command = has_paths(paths, file);
		if (command)
			return (command);
	}
	else if (!is_builtin(file))
	{
		if (access(file, F_OK | X_OK) == 0)
			return (file);
		ft_putstr_fd("minishell: ", 2);
		error_msg(file, 126);
	}
	return (NULL);
}

static char	*has_paths(char **paths, char *file)
{
	char	*command;
	char	*temp;

	if (!ft_strncmp("./", file, 2) || !is_here(file))
	{
		if (access(file, F_OK | X_OK) == 0)
			return (file);
		ft_putstr_fd("minishell: ", 2);
		error_msg(file, 126);
	}
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
	return (NULL);
}

static int	is_here(char *file)
{
	int	i;

	i = -1;
	while (file[++i])
		if (file[i] == '/')
			return (0);
	return (1);
}

static void	check_directories(char *file)
{
	DIR	*dir;

	if (!ft_strncmp(".", file, ft_strlen(file)))
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		exit_msg(".: usage: . filename [arguments]", 2);
	}
	if (!ft_strncmp("..", file, ft_strlen(file)))
		exit_msg("..: command not found\n", 127);
	dir = opendir(file);
	if (dir)
	{
		closedir(dir);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		exit_msg(": Is a directory\n", 2);
	}
}
