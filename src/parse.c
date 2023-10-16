/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:59:05 by gfernand          #+#    #+#             */
/*   Updated: 2023/10/16 17:10:00 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_parse_struct(t_parse *parse);

void	start_parse(char *input)
{
	t_parse	*parse;
	char	**str_pipe;
	int		i;
	int		j;

	parse = malloc (sizeof (t_parse));
	init_parse_struct(parse);
	if (!check_rps(input, '|') || !check_rps(input, '<') || !check_rps(input, '>'))
		return ;
	str_pipe = split_quote(input, '|');
	parse->ncommands = 0;
	while (str_pipe[parse->ncommands])
		parse->ncommands++;
	printf("commands %d\n", parse->ncommands);
	parse->command = ((char ***) malloc (sizeof (char **) * (parse->ncommands + 1)));
	parse->command[parse->ncommands] = NULL;
	i = -1;
	while (str_pipe[++i] && str_pipe[i][0])
	{
		parse->command[i] = split_quote(str_pipe[i], ' ');
		printf("%d PIPE - %s\n", i, str_pipe[i]);
		j = -1;
		while (parse->command[i][++j] && parse->command[i][j][0])
		{
			parse->command[i][j] = remove_matched_quotes(parse->command[i][j]);
			printf("----SPACE %d- %s\n", j, parse->command[i][j]);
		}
	}
	ft_splitfree(str_pipe);
	i = -1;
	while (parse->command[++i])
		ft_splitfree(parse->command[i]);
	free(parse->command);
	free(parse);
}

static void	init_parse_struct(t_parse *parse)
{
	parse->ncommands = 0;
	parse->command = NULL;
}
