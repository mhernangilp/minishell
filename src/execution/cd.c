/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:36:21 by mhernang          #+#    #+#             */
/*   Updated: 2023/11/26 18:36:23 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*set_chdir(char **commands);
static int	check_dir(char *chdirectory);
static char	*get_pwd(void);
static int	chpwd(void);

int	cd(char **commands)
{
	char	*chdirectory;

	if (commands[1] && commands[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (!commands[1][0])
		return (0);
	chdirectory = set_chdir(commands);
	if (!chdirectory)
		return (1);
	if (check_dir(chdirectory))
		return (1);
	if (chdir(chdirectory) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(chdirectory);
		return (1);
	}
	if (chpwd())
		return (1);
	return (0);
}

static char	*set_chdir(char **commands)
{
	char	*chdirectory;

	if (!commands[1])
	{
		chdirectory = getenv_value("HOME");
		if (!chdirectory)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (NULL);
		}
	}
	else
		chdirectory = commands[1];
	return (chdirectory);
}

static int	check_dir(char *chdirectory)
{
	DIR		*dir;

	dir = opendir(chdirectory);
	if (!dir)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(chdirectory);
		return (1);
	}
	closedir(dir);
	return (0);
}

static int	chpwd(void)
{
	char	*pwd;
	char	*pwd_env;

	pwd = get_pwd();
	if (!pwd)
		return (1);
	pwd_env = ft_strjoin("PWD=", pwd);
	if (!pwd_env)
		return (1);
	add(pwd_env, NORMAL);
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
