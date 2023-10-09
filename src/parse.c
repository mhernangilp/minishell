/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:59:05 by gfernand          #+#    #+#             */
/*   Updated: 2023/10/09 15:01:29 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_pipes(char *input);

void	start_parse(t_parse *parse, char *input)
{
	char	**str_pipe;
	int		i;
	int		j;

	check_pipes(input);
	str_pipe = split_quote(input, '|');
	parse->ncommands = 0;
	while (str_pipe[parse->ncommands])
		parse->ncommands++;
	printf("commands %d\n", parse->ncommands);
	parse->command = ((char ***) malloc (sizeof (char **) * parse->ncommands));
	i = -1;
	while (str_pipe[++i] && str_pipe[i][0])
	{
		parse->command[i] = split_quote(str_pipe[i], ' ');
		printf("%d PIPE - %s\n", i, str_pipe[i]);
		j = -1;
		while (parse->command[i][++j] && parse->command[i][j][0])
		{
			parse->command[i][j] = remove_matched_quotes(parse->command[i][j]);
			printf("SPACE %d - %s\n", j, parse->command[i][j]);
		}
	}
	ft_splitfree(str_pipe);
	/*i = -1;
	while (parse->command[++i])
		ft_splitfree(parse->command[i]);*/
	free(parse->command);
}

char	*remove_matched_quotes(const char *s)
{
	char	*result;
	int		i;
	int		j;
	int		inside_quotes;

	result = (char *)malloc(ft_strlen(s) + 1);
	if (result == NULL)
		putexit("Error de memoria\n");
	i = -1;
	j = -1;
	inside_quotes = 0;
	while (s[++i])
	{
		if (s[i] == '\'' && !inside_quotes)
			inside_quotes = 1;
		else if (s[i] == '\'' && inside_quotes == 1)
			inside_quotes = 0;
		else if (s[i] == '"' && !inside_quotes)
			inside_quotes = 2;
		else if (s[i] == '"' && inside_quotes == 2)
			inside_quotes = 0;
		else
			result[++j] = s[i];
	}
	result[ft_strlen(s)] = '\0';
	free((char *) s);
	return (result);
}

static void	check_pipes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (i == 0 || input[i] == '|')
		{
			if ((input[i] == '|' && input[i + 1] == '|') || input[0] == '|')
			{
				if (input[i + 2] == '|' && input[i + 3] == '|')
					putexit("syntax error near unexpected token `||'");
				else if (input[i + 2] == '|' || input[0] == '|')
					putexit("syntax error near unexpected token `|'");
			}
			if (i == 0 && input[i] == '|')
				break ;
			i++;
			while (input[i] == ' ')
				i++;
			if (input[i] == '|' && input[i - 1] != '|')
				putexit("syntax error near unexpected token `|'");
		}
		if (input[i] != '|')
			i++;
	}
}
