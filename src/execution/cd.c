/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:36:21 by mhernang          #+#    #+#             */
/*   Updated: 2023/12/21 18:13:17 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*set_chdir(t_bridge *bridge, char **commands);
static int	check_dir(char *chdirectory, char *arg);
static char	*get_pwd(void);
static int	chpwd(t_bridge *bridge);

int	cd(t_bridge *bridge, char **commands)
{
	char	*chdirectory;

	if (commands[1] && commands[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (commands[1] && !commands[1][0])
		return (0);
	chdirectory = set_chdir(bridge, commands);
	if (!chdirectory)
		return (1);
	if (check_dir(chdirectory, commands[1]))
		return (1);
	if (chdir(chdirectory) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(chdirectory);
		free(chdirectory);
		return (1);
	}
	free(chdirectory);
	if (chpwd(bridge))
		return (1);
	return (0);
}

static char	*parse_chdir(char *arg, t_bridge *bridge)
{
	char	*ret;

	if (arg[0] == '~')
	{
		ret = ft_strjoin(getenv_value(bridge -> m_env, "HOME"), &arg[1]);
	}
	else
		ret = ft_strdup(arg);
	return (ret);
}

static char	*set_chdir(t_bridge *bridge, char **commands)
{
	char	*chdirectory;

	if (!commands[1])
	{
		chdirectory = ft_strdup(getenv_value(bridge -> m_env, "HOME"));
		if (!chdirectory)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (NULL);
		}
	}
	else
		chdirectory = parse_chdir(commands[1], bridge);
	return (chdirectory);
}

static int	check_dir(char *chdirectory, char *arg)
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

static int	chpwd(t_bridge *bridge)
{
	char	*pwd;
	char	*pwd_env;

	pwd = get_pwd();
	if (!pwd)
		return (1);
	pwd_env = ft_strjoin("PWD=", pwd);
	if (!pwd_env)
		return (1);
	add(&bridge -> m_env, pwd_env, NORMAL);
	free(pwd);
	free(pwd_env);
	return (0);
}

static char	*get_pwd(void)
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, PATH_MAX))
		return (NULL);
	return (ft_strdup(pwd));
}
