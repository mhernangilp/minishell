/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:59:05 by gfernand          #+#    #+#             */
/*   Updated: 2023/10/30 11:03:41 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	init_bridge_struct(t_bridge *bridge);
static void	do_bridge(t_bridge *bridge, char **str_pipe);
static void	free_commands(t_bridge *bridge, char **str_pipe);

void	start_parse(char *input)
{
	t_bridge	*bridge;
	char		**str_pipe;

	if (!check_rps(input, '|'))
		return ;
	bridge = malloc (sizeof (t_bridge));
	init_bridge_struct(bridge);
	str_pipe = split_quote(input, '|');
	while (str_pipe[bridge->n_cmds])
	{
		if (!check_rps(str_pipe[bridge->n_cmds], '<')
			|| !check_rps(str_pipe[bridge->n_cmds], '>'))
			return ;
		bridge->n_cmds++;
	}
	bridge->commands = malloc (sizeof (char **) * (bridge->n_cmds + 1));
	bridge->redirect = malloc (sizeof (t_cmdred) * (bridge->n_cmds + 1));
	if (!bridge->commands)
		putexit("Malloc error\n");
	bridge->commands[bridge->n_cmds] = NULL;
	do_bridge(bridge, str_pipe);
	free_commands(bridge, str_pipe);
}

static void	do_bridge(t_bridge *bridge, char **str_pipe)
{
	int		i;
	int		j;
	t_parse	*parse;

	parse = malloc (sizeof (t_parse));
	if (!parse)
		putexit("Malloc error\n");
	str_pipe = fill_redirections(parse, bridge, str_pipe);
	i = -1;
	while (str_pipe[++i] && str_pipe[i][0])
	{
		printf("%d PIPE->%s<-\n", i, str_pipe[i]);
		bridge->commands[i] = split_quote(str_pipe[i], ' ');
		j = -1;
		while (bridge->commands[i][++j] && bridge->commands[i][j][0])
		{
			bridge->commands[i][j] = environments(parse, bridge->commands[i][j]);
			bridge->commands[i][j] = remove_quotes(bridge->commands[i][j]);
			printf("\t %dCOMMAND->%s<-\n", j, bridge->commands[i][j]);
		}
	}
}

static void	free_commands(t_bridge *bridge, char **str_pipe)
{
	int	i;

	ft_splitfree(str_pipe);
	i = -1;
	while (bridge->commands[++i])
	{
		ft_splitfree(bridge->commands[i]);
		//free (bridge->redirect);
	}
	free(bridge->commands);
	free(bridge);
}

static void	init_bridge_struct(t_bridge *bridge)
{
	bridge->n_cmds = 0;
	bridge->commands = NULL;
	bridge->redirect = NULL;
}
