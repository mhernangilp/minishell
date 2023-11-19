#include "../../minishell.h"
#include <stdio.h>

int	echo(char **commands)
{
	int	start;

	if (!commands[1])
	{	
		write(1, "\n", 1);
		return (0);
	}
	start = 0;
	if (!ft_strncmp(commands[1], "-n", 2))
		start = 1;
	while (commands[++start])
	{
		ft_putstr_fd(commands[start], 1);
		if (commands[start + 1])
			write(1, " ", 1);
	}
	if (ft_strncmp(commands[1], "-n", 2))
		write(1, "\n", 1);
	return (0);
}
