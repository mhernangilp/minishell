/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:02:26 by gfernand          #+#    #+#             */
/*   Updated: 2023/11/13 12:29:43 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*void	leaks(void)
{
	system("leaks minishell");
}*/

static void	free_commands(t_bridge *bridge);

int	g_ret_val = 0;

int	main(int argc, char **argv, char **envp)
{
	t_bridge	*bridge;
	char		*input;

	//atexit(leaks);
	(void) argv;
	if (argc != 1)
		putexit("Wrong parameters\n");
	while (1)
	{
		input_signals();
		input = readline(ENTRADA_MS);
		if (input == NULL)
		{
			printf("\033[F\33[2K\r");
			printf("%sexit\n", ENTRADA_MS);
			exit(1);
		}
		add_history(input);
		bridge = start_parse(input);
		if (bridge != NULL)
			execution(bridge, envp);
	//	bridge = test_execution();
		free(input);
		free_commands(bridge);
	}
	return (0);
}

void	putexit(char *s)
{
	printf("%s", s);
	exit(0);
}

static void	free_commands(t_bridge *bridge)
{
	int	i;

	if (!bridge)
		return ;
	i = -1;
	while (bridge->commands[++i])
	{
		ft_splitfree(bridge->commands[i]);
		//free (bridge->redirect);
	}
	free(bridge->commands);
	free(bridge);
}
