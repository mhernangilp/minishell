/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:59:05 by gfernand          #+#    #+#             */
/*   Updated: 2023/09/26 17:37:08 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_pipes(char *input);
static void	delete_spaces(char *input);

void	start_parse(t_parse *parse, char *input)
{
	char	**str_pipe;
	int		i;
	int		j;

	check_pipes(input);
	str_pipe = split_quote(input, '|');
	parse->commands = 0;
	while (str_pipe[parse->commands])
		parse->commands++;
	printf("commands %d\n", parse->commands);
	parse->str_space = ((char ***) malloc (sizeof (char **) * parse->commands));
	i = -1;
	while (str_pipe[++i] && str_pipe[i][0])
	{
		parse->str_space[i] = split_quote(str_pipe[i], ' ');
		printf("%d PIPE - %s\n", i, str_pipe[i]);
		j = -1;
		while (parse->str_space[i][++j] && parse->str_space[i][j][0])
			printf("SPACE %d - %s\n", j, parse->str_space[i][j]);
	}
	ft_splitfree(str_pipe);
	free(parse->str_space);
}

static void	check_pipes(char *input)
{
	int	i;

	/* HAY QUE TENER EN CUENTA EL COMPORTAMIENTO DE MAS DE UN PIPE SEGUIDO */
	i = -1;
	while (input[++i])
	{
		if (input[i] == '|')
		{
			if (input[i + 1] == '|')
			{
				if (input[i + 2] == '|' && input[i + 3] == '|')
					//ERROR, SON MAS DE TRES (||)
					putexit("syntax error near unexpected token `||'");
				else if (input[i + 2] == '|')
					//ERROR SON TRES (|)
					putexit("syntax error near unexpected token `|'");
				//BIEN, SON DOS
			}
		}
	}
	delete_spaces(input);
}

static void	delete_spaces(char *input)
{
	int	i;

	i = 0;
	if (input[i] == '|')
		putexit("syntax error near unexpected token `|'");
	
	while (input[i])
	{
		if (i == 0 || input[i] == '|')
		{
			if (i == 0 && input[i] != ' ' && input[i] == '|')
				break;
			i++;
			while (input[i] == ' ')
				i++;
			if (input[i] == '|' && input[i - 1] != '|')
				putexit("syntax error near unexpected token `|'");
			if (input[i] != '|')
				i++;
		}
		else
			i++;
	}
}
