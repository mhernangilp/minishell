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

void	check_pipes(t_parse *parse, char *input)
{
	char	**str_pipe;
	int		i;
	int		j;
	int		history;

	/* HAY QUE TENER EN CUENTA EL COMPORTAMIENTO DE MAS DE UN PIPE SEGUIDO */
	/*	
	i = -1;
	while (input[++i])
	{
		if (input[i] == '|')
		{
			if (input[i + 1] == '|')
			{
				if (input[i + 2] == '|' && input[i + 3] == '|')
					break; //ERROR, SON MAS DE TRES (||)
				else if (input[i + 2] == '|')
					break; //ERROR SON TRES (|)
				//BIEN, SON DOS
			}
		}
	}
	*/
	history = open(".history", O_WRONLY | O_CREAT | O_APPEND,
			S_IRUSR | S_IWUSR);
	write(history, input, strlen(input));
	write(history, "\n", 1);
	str_pipe = ft_split(input, '|');
	parse->commands = 0;
	while (str_pipe[parse->commands])
		parse->commands++;
	parse->str_space = ((char ***) malloc (sizeof (char **) * parse->commands));
	i = -1;
	while (str_pipe[++i] && str_pipe[i][0])
	{
		parse->str_space[i] = ft_split(str_pipe[i], ' ');
		printf("%d PIPE - %s\n", i, str_pipe[i]);
		j = -1;
		while (parse->str_space[i][++j] && parse->str_space[i][j][0])
			printf("SPACE %d - %s\n", j, parse->str_space[i][j]);
	}
	ft_splitfree(str_pipe);
	/*i = -1;
	while (parse->str_space[++i])
		ft_splitfree(parse->str_space[i]);*/
	free(parse->str_space);
}
