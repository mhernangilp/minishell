/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:02:26 by gfernand          #+#    #+#             */
/*   Updated: 2023/10/15 16:47:53 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*void	leaks(void)
{
	system("leaks minishell");
}*/

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_bridge	*bridge;

	//atexit(leaks);
	(void) argv;
	if (argc != 1)
		putexit("Wrong parameters\n");
	while (1)
	{
		input = readline(ENTRADA_MS);
		if (input == NULL)
		{
			printf("exit\n");
			exit(1);
		}
		add_history(input);
		start_parse(input);
		bridge = test_execution();
		execution(bridge, envp);
		free(input);
	}
	return (0);
}

void	putexit(char *s)
{
	printf("%s", s);
	exit(0);
}
