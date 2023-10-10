/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:02:26 by gfernand          #+#    #+#             */
/*   Updated: 2023/10/09 17:20:54 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_parse_struct(t_parse *parse);

void	leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv)
{
	char	*input;
	t_parse	*parse;

	atexit(leaks);
	(void) argv;
	if (argc != 1)
		putexit("Wrong parameters\n");
	parse = malloc (sizeof (t_parse));
	while (1)
	{
		init_parse_struct(parse);
		input = readline(ENTRADA_MS);
		printf("ENTRA");
		if (input == NULL)
		{
			printf("exit\n");
			exit(1);
		}
		add_history(input);
		start_parse(parse, input);
		free(input);
	}
	free(parse);
	return (0);
}

static void	init_parse_struct(t_parse *parse)
{
	parse->ncommands = 0;
	parse->command = NULL;
}

void	putexit(char *s)
{
	printf("%s", s);
	exit(1);
}
