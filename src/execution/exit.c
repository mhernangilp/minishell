#include "../../minishell.h"

static void	finish(int ret);

int	b_exit(char **commands)
{
	if (!commands[1])
		finish(0);
	if (!commands[2])
	{
		if (ft_atoi(commands[1]) > 0)
			finish(ft_atoi(commands[1]));
		if (ft_atoi(commands[1]) < 0)
			finish(255 + ft_atoi(commands[1]));
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minishell: exit: ", 1);
		ft_putstr_fd(commands[1], 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		exit (2);
	}
	ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("minishell: exit: too many arguments\n", 1);
	return (1);
}

static void	finish(int ret)
{
	ft_putstr_fd("exit\n", 1);
	exit (ret);
}
