/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:51:25 by mhernang          #+#    #+#             */
/*   Updated: 2023/12/26 14:58:35 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

char	*last_pwd(char *arg, t_bridge *bridge)
{
	char	*oldpwd;

	oldpwd = getenv_value(bridge -> m_env, "OLDPWD");
	if (!arg[1])
	{
		if (!oldpwd)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (NULL);
		}
		ft_putstr_fd(oldpwd, 1);
		ft_putchar_fd('\n', 1);
		return (ft_strdup(getenv_value(bridge -> m_env, "OLDPWD")));
	}
	return (ft_strdup(arg));
}

char	*parse_chdir(char *arg, t_bridge *bridge)
{
	char	*ret;

	if (arg[0] == '~')
	{
		ret = ft_strjoin(getenv_value(bridge -> m_env, "HOME"), &arg[1]);
	}
	else if (arg[0] == '-')
		ret = last_pwd(arg, bridge);
	else
		ret = ft_strdup(arg);
	return (ret);
}

int	check_dir(char *chdirectory, char *arg)
{
	DIR		*dir;

	dir = opendir(chdirectory);
	if (!dir)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		if (arg[1] == '~')
			perror(arg);
		else
			perror(chdirectory);
		free(chdirectory);
		return (1);
	}
	closedir(dir);
	return (0);
}
