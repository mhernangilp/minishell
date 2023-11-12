#include "../../minishell.h"

int	cd(char **commands)
{
	char	*chdirectory;
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
	//cambiar env pwd
	return (error);
}
