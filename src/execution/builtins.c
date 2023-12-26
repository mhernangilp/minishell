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

void	builtins(t_bdg *bridge, char **commands, int type)
{
	if (!ft_strncmp(commands[0], "cd", ft_strlen(commands[0])))
		set_ret_val(bridge, cd(bridge, commands));
	if (!ft_strncmp(commands[0], "pwd", ft_strlen(commands[0])))
		set_ret_val(bridge, pwd());
	if (!ft_strncmp(commands[0], "env", ft_strlen(commands[0])))
		set_ret_val(bridge, env(bridge -> m_env));
	if (!ft_strncmp(commands[0], "unset", ft_strlen(commands[0])))
		set_ret_val(bridge, unset(bridge, commands));
	if (!ft_strncmp(commands[0], "export", ft_strlen(commands[0])))
		set_ret_val(bridge, b_export(bridge, commands));
	if (!ft_strncmp(commands[0], "echo", ft_strlen(commands[0])))
		set_ret_val(bridge, echo(commands));
	if (!ft_strncmp(commands[0], "exit", ft_strlen(commands[0])))
		set_ret_val(bridge, b_exit(commands, type));
}
