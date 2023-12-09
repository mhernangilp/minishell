/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:02:26 by gfernand          #+#    #+#             */
/*   Updated: 2023/12/04 16:00:33 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*void	leaks(void)
{
	system("leaks minishell");
}*/

static void	ctr(void);
static void	minishell();
static void	free_commands(t_bridge *bridge);

char	**g_env;

int	main(int argc, char **argv, char **envp)
{
	//atexit(leaks);
	(void) argv;
	if (argc != 1)
		exit_msg("Wrong parameters\n", 1);
	g_env = dup_env(envp);
	add("?=0", RETVAL);
	ctr();
	while (1)
		minishell();
	return (0);
}

static void	minishell()
{
	t_bridge	*bridge;
	char		*input;

	bridge = NULL;
	input_signals();
	input = readline(ENTRADA_MS);
	if (input == NULL)
	{
		ft_putstr_fd("\033[1A\033[2K", 1);
		ft_putstr_fd(ENTRADA_MS, 1);
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	if (*input)
	{
		add_history(input);
		bridge = start_parse(input);
		if (bridge != NULL)
			execution(bridge);
	}
	free(input);
	free_commands(bridge);
}

static void	free_commands(t_bridge *bridge)
{
	int	i;

	if (!bridge)
		return ;
	i = -1;
	while (bridge->commands[++i])
		ft_splitfree(bridge->commands[i]);
	free(bridge->commands);
	i = -1;
	while (bridge->redirect && (bridge->redirect[++i].inred
		|| bridge->redirect[i].outred))
	{
		if (bridge->redirect[i].inred)
		{
			ft_splitfree(bridge->redirect[i].inred->file);
			free (bridge->redirect[i].inred);
		}
		if (bridge->redirect[i].outred)
		{
			ft_splitfree(bridge->redirect[i].outred->file);
			free (bridge->redirect[i].outred);
		}
	}
	if (bridge->redirect)
		free (bridge->redirect);
	free(bridge);
}

static void	ctr(void)
{
	int				x;
	struct termios	termios;

	x = tcgetattr(0, &termios);
	if (x)
	{
		perror("");
		exit(1);
	}
	termios.c_lflag &= ~ECHOCTL;
	x = tcsetattr(0, 0, &termios);
	if (x)
	{
		perror("");
		exit(1);
	}
}
