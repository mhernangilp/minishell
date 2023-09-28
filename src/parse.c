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

void	check_pipes(char *input)
{
	char	**str_pipe;
	char	***str_space;
	int		i;
	int		j;

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
	str_pipe = ft_split(input, '|');
	i = 0;
	while (str_pipe[i])
		i++;
	str_space = ((char ***) malloc (sizeof (char **) * i));
	i = -1;
	j = -1;
	while (str_pipe[++i] && str_pipe[i][0])
	{
		str_space[i] = ft_split(str_pipe[i], ' ');
		printf("PIPE %d - %s\n", i, str_pipe[i]);
		while (str_space[i][++j] && str_space[i][j][0])
			printf("SPACE %d - %s\n", j, str_space[i][j]);
	}
	ft_splitfree(str_pipe);
	/*i = -1;
	while (str_space[++i] && str_space[i][0] && str_space[i][0][0])
		ft_splitfree(str_space[i]);*/
	free(str_space);
}
