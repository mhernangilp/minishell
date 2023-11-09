#include "../../minishell.h"

int	cd(char **commands)
{
	if (commands[1] && commands[2])
		return (1);
	if (!commands[1] || *commands[1] == '\0')
		return (1);
	return (chdir(commands[1]));
}
