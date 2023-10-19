/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:59:05 by gfernand          #+#    #+#             */
/*   Updated: 2023/10/17 18:27:12 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_bridge_struct(t_bridge *bridge);

void	start_parse(char *input)
{
	t_bridge	*bridge;
	char	**str_pipe;
	int		i;
	int		j;

	bridge = malloc (sizeof (t_bridge));
	init_bridge_struct(bridge);
	if (!check_rps(input, '|') || !check_rps(input, '<') || !check_rps(input, '>'))
		return ;
	str_pipe = split_quote(input, '|');
	while (str_pipe[bridge->n_cmds])
		bridge->n_cmds++;
	printf("commands %d\n", bridge->n_cmds);
	bridge->command = ((char ***) malloc (sizeof (char **) * (bridge->n_cmds + 1)));
	bridge->command[bridge->n_cmds] = NULL;
	i = -1;
	while (str_pipe[++i] && str_pipe[i][0])
	{
		bridge->command[i] = split_quote(str_pipe[i], ' ');
		printf("%d PIPE - %s\n", i, str_pipe[i]);
		j = -1;
		while (bridge->command[i][++j] && bridge->command[i][j][0])
		{
			bridge->command[i][j] = environments(bridge->command[i][j]);
			bridge->command[i][j] = remove_matched_quotes(bridge->command[i][j]);
			printf("----SPACE %d- %s\n", j, bridge->command[i][j]);
		}
	}
	ft_splitfree(str_pipe);
	i = -1;
	while (bridge->command[++i])
		ft_splitfree(bridge->command[i]);
	free(bridge->command);
	free(bridge);
}

/*
 *	redirecciones (<, <<, >, >>, |)
 *
 *	expansion de variables ($PATH, $USER...)
 *
 * */

static void	init_bridge_struct(t_bridge *bridge)
{
	bridge->n_cmds = 0;
	bridge->command = NULL;
}
