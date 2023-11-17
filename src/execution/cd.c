#include "../../minishell.h"
#include <linux/limits.h>

static	char	*get_pwd();

int	cd(char **commands)
{
	char	*chdirectory;
	char	*pwd;
	char	*pwd_env;
	int		error;

	if (commands[1] && commands[2])
		return (1);
	if (!commands[1])
		chdirectory = getenv("HOME"); // comprobar si home existe
	else
		chdirectory = commands[1];
	if (*chdirectory == '\0')
		return (1);
	error = chdir(chdirectory);
	pwd = get_pwd();
	if (!pwd)
		return (1);
	pwd_env = ft_strjoin("PWD=", pwd);
	if (!pwd_env)
		return (1);
	add(pwd_env);
	free(pwd);
	free(pwd_env);
	return (error);
}

static char	*get_pwd()
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, PATH_MAX))
		return (NULL);
	return(ft_strdup(pwd));
}
