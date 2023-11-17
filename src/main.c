/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:02:26 by gfernand          #+#    #+#             */
/*   Updated: 2023/11/12 20:34:07 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*void	leaks(void)
{
	system("leaks minishell");
}*/

static void	free_commands(t_bridge *bridge);

char	**g_env;

int	main(int argc, char **argv, char **envp)
{
	t_bridge	*bridge;
	char		*input;

	//atexit(leaks);
	(void) argv;
	if (argc != 1)
		putexit("Wrong parameters\n");
	g_env = dup_env(envp);
	while (1)
	{
		input = readline(ENTRADA_MS);
		if (input == NULL || !strcmp(input, "exit"))
		{
			printf("exit\n");
			exit(0);
		}
		if (*input)
		{
			add_history(input);
			bridge = start_parse(input);
			if (bridge != NULL)
				execution(bridge);
		}
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
