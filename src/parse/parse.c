/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:59:05 by gfernand          #+#    #+#             */
/*   Updated: 2023/11/05 18:49:06 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	init_bridge_struct(t_bridge *bridge);
static void	do_bridge(t_bridge *bridge, char **str_pipe);

t_bridge	*start_parse(char *input)
{
	t_bridge	*bridge;
	char		**str_pipe;

	if (!check_input(input))
		return (NULL);
	bridge = malloc (sizeof (t_bridge));
	if (!check_rps(input, '|'))
		return (NULL);
	init_bridge_struct(bridge);
	str_pipe = split_quote(input, '|');
	while (str_pipe[bridge->n_cmds])
	{
		if (!check_rps(str_pipe[bridge->n_cmds], '<')
			|| !check_rps(str_pipe[bridge->n_cmds], '>'))
			return (NULL);
		bridge->n_cmds++;
	}
	bridge->commands = malloc (sizeof (char **) * (bridge->n_cmds + 1));
	bridge->redirect = malloc (sizeof (t_cmdred) * (bridge->n_cmds + 1));
	if (!bridge->commands || !bridge->redirect)
		exit_msg(ERR_MEMORY, 1);
	bridge->commands[bridge->n_cmds] = NULL;
	do_bridge(bridge, str_pipe);
	ft_splitfree(str_pipe);
	return (bridge);
}

static void	do_bridge(t_bridge *bridge, char **str_pipe)
{
	int		i;
	int		j;
	t_parse	*parse;

	parse = malloc (sizeof (t_parse));
	if (!parse)
		exit_msg(ERR_MEMORY, 1);
	str_pipe = fill_redirections(parse, bridge, str_pipe);
	i = -1;
	while (str_pipe[++i] && str_pipe[i][0])
	{
		bridge->commands[i] = split_quote(str_pipe[i], ' ');
		j = -1;
		while (bridge->commands[i][++j] && bridge->commands[i][j][0])
		{
			bridge->commands[i][j] = environments(parse, bridge->commands[i][j]);
			bridge->commands[i][j] = remove_quotes(bridge->commands[i][j]);
		}
	}
}

static void	init_bridge_struct(t_bridge *bridge)
{
	bridge->n_cmds = 0;
	bridge->commands = NULL;
	bridge->redirect = NULL;
}
