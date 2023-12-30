/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:36:21 by mhernang          #+#    #+#             */
/*   Updated: 2023/12/26 15:01:08 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*set_chdir(t_bdg *bridge, char **commands);
static int	chdir_err(char *chdirectory);
static int	chpwd(t_bdg *bridge);

int	cd(t_bdg *bridge, char **commands)
{
	char	*chdirectory;
	char	*oldpwd;

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
		return (chdir_err(chdirectory));
	oldpwd = ft_strjoin("OLDPWD=", getenv_value(bridge -> m_env, "PWD"));
	add(&bridge -> m_env, oldpwd, RETVAL);
	free(oldpwd);
	free(chdirectory);
	if (chpwd(bridge))
		return (1);
	return (0);
}

static int	chdir_err(char *chdirectory)
{
	ft_putstr_fd("minishell: cd: ", 2);
	perror(chdirectory);
	free(chdirectory);
	return (1);
}

static char	*set_chdir(t_bdg *bridge, char **commands)
{
	char	*chdirectory;

	if (!commands[1] || (commands[1] && commands[1][0] && commands[1][1]
				&& !commands[1][2] && commands[1][0] == '-'
				&& commands[1][1] == '-'))
	{
		if (!getenv_value(bridge -> m_env, "HOME"))
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (NULL);
		}
		chdirectory = ft_strdup(getenv_value(bridge -> m_env, "HOME"));
	}
	else
		chdirectory = parse_chdir(commands[1], bridge);
	return (chdirectory);
}

static int	chpwd(t_bdg *bridge)
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

char	*get_pwd(void)
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, PATH_MAX))
		return (NULL);
	return (ft_strdup(pwd));
}
