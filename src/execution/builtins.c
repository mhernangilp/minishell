/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:35:57 by mhernang          #+#    #+#             */
/*   Updated: 2023/11/26 18:36:00 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_parent_builtin(char *command)
{
	if (!ft_strncmp(command, "cd", ft_strlen(command)))
		return (1);
	if (!ft_strncmp(command, "export", ft_strlen(command)))
		return (1);
	if (!ft_strncmp(command, "unset", ft_strlen(command)))
		return (1);
	if (!ft_strncmp(command, "exit", ft_strlen(command)))
		return (1);
	return (0);
}

int	is_builtin(char *command)
{
	if (!ft_strncmp(command, "echo", ft_strlen(command)))
		return (1);
	if (!ft_strncmp(command, "cd", ft_strlen(command)))
		return (1);
	if (!ft_strncmp(command, "pwd", ft_strlen(command)))
		return (1);
	if (!ft_strncmp(command, "export", ft_strlen(command)))
		return (1);
	if (!ft_strncmp(command, "unset", ft_strlen(command)))
		return (1);
	if (!ft_strncmp(command, "env", ft_strlen(command)))
		return (1);
	if (!ft_strncmp(command, "exit", ft_strlen(command)))
		return (1);
	return (0);
}

void	builtins(char **commands, int type)
{
	if (!ft_strncmp(commands[0], "cd", ft_strlen(commands[0])))
		set_ret_val(cd(commands));
	if (!ft_strncmp(commands[0], "pwd", ft_strlen(commands[0])))
		set_ret_val(pwd());
	if (!ft_strncmp(commands[0], "env", ft_strlen(commands[0])))
		set_ret_val(env());
	if (!ft_strncmp(commands[0], "unset", ft_strlen(commands[0])))
		set_ret_val(unset(commands));
	if (!ft_strncmp(commands[0], "export", ft_strlen(commands[0])))
		set_ret_val(b_export(commands));
	if (!ft_strncmp(commands[0], "echo", ft_strlen(commands[0])))
		set_ret_val(echo(commands));
	if (!ft_strncmp(commands[0], "exit", ft_strlen(commands[0])))
		set_ret_val(b_exit(commands, type));
}
