#include "../../minishell.h"
#include <dirent.h>
#include <linux/limits.h>
#include <stdio.h>

static char	*get_pwd();
static int	chpwd();

int	cd(char **commands)
{
	char	*chdirectory;
	DIR	*dir;

	if (commands[1] && commands[2])
	{
		ft_putstr_fd("too many arguments\n", 2);
		return (1);
	}
	if (!commands[1])
	{
		chdirectory = getenv_value("HOME");
		if (!chdirectory)
		{
			ft_putstr_fd("HOME not set\n", 2);
			return (1);
		}
	}
	else
		chdirectory = commands[1];
	dir = opendir(chdirectory);
	if (!dir)
	{
		perror(chdirectory);
		return (1);
	}
	closedir(dir);
	if (chdir(chdirectory) == -1)
	{
		perror(chdirectory);
		return (1);
	}
	if (chpwd())
		return (1);
	return (0);
}

static int	chpwd()
{
	char	*pwd;
	char	*pwd_env;

	pwd = get_pwd();
	if (!pwd)
		return (1);
	pwd_env = ft_strjoin("PWD=", pwd);
	if (!pwd_env)
		return (1);
	add(pwd_env);
	free(pwd);
	free(pwd_env);
	return (0);
}

static char	*get_pwd()
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, PATH_MAX))
		return (NULL);
	return(ft_strdup(pwd));
}
