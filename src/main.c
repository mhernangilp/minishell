/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:02:26 by gfernand          #+#    #+#             */
/*   Updated: 2023/09/26 14:08:34 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_parse_struct(t_parse *parse);

int	main(int argc, char **argv)
{
	char	*input;
	t_parse	*parse;

	(void) argv;
	if (argc != 1)
		putexit("Wrong parameters\n");
	parse = malloc (sizeof (t_parse));
	init_parse_struct(parse);
	while (1)
	{
		input = readline(ENTRADA_MS);
		if (input == NULL)
		{
			printf("exit\n");
			exit(1);
		}
		add_history(input);
		check_pipes(parse, input);
	/*	CREAR HISTORIAL
		PARSEO
		EJECUCIÓN
			(builtins(input))*/
		free(input);
	}
	return (0);
}

static void	init_parse_struct(t_parse *parse)
{
	parse->commands = 0;
	parse->str_space = NULL;
}

void	putexit(char *s)
{
	printf("%s", s);
	exit(1);
}
