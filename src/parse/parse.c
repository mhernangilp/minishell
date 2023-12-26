/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:59:05 by gfernand          #+#    #+#             */
/*   Updated: 2023/12/19 16:37:26 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_bridge	*init_bridge_struct(void);
static t_parse	*malloc_bridge_and_parse(t_bridge *bridge);
static void		do_bridge(t_bridge *bridge, char **str_pipe);

t_bridge	*start_parse(char *input, char **m_env)
{
	t_bridge	*bridge;
	char		**str_pipe;

	bridge = init_bridge_struct();
	bridge->m_env = m_env;
	if (!check_input(input) || !check_rps(bridge, input, '|'))
	{
		bridge->ret = -1;
		return (bridge);
	}
	str_pipe = split_quote(input, '|');
	while (str_pipe[bridge->n_cmds])
	{
		if (!check_rps(bridge, str_pipe[bridge->n_cmds], '<')
			|| !check_rps(bridge, str_pipe[bridge->n_cmds], '>'))
		{
			bridge->ret = -1;
			return (bridge);
		}
		bridge->n_cmds++;
	}
	do_bridge(bridge, str_pipe);
	ft_splitfree(str_pipe);
	return (bridge);
}

static void	do_bridge(t_bridge *bridge, char **str_pipe)
{
	int		i;
	int		j;
	t_parse	*parse;

	parse = malloc_bridge_and_parse(bridge);
	str_pipe = fill_redirections(parse, bridge, str_pipe);
	i = -1;
	while (str_pipe[++i] && str_pipe[i][0])
	{
		bridge->commands[i] = split_quote(str_pipe[i], ' ');
		j = -1;
		while (bridge->commands[i][++j] && bridge->commands[i][j][0])
		{
			bridge->commands[i][j] = environments(parse,
					bridge->commands[i][j]);
			bridge->commands[i][j] = remove_quotes(bridge->commands[i][j]);
		}
	}
	free(parse);
}

static t_parse	*malloc_bridge_and_parse(t_bridge *bridge)
{
	t_parse	*parse;

	bridge->commands = malloc (sizeof (char **) * (bridge->n_cmds + 1));
	bridge->redirect = malloc (sizeof (t_cmdred) * (bridge->n_cmds + 1));
	if (!bridge->commands || !bridge->redirect)
		exit_msg(ERR_MEMORY, 1);
	bridge->commands[bridge->n_cmds] = NULL;
	parse = malloc (sizeof (t_parse));
	if (!parse)
		exit_msg(ERR_MEMORY, 1);
	parse->bridge = bridge;
	return (parse);
}

static t_bridge	*init_bridge_struct(void)
{
	t_bridge	*bridge;

	bridge = malloc (sizeof (t_bridge));
	if (!bridge)
		exit_msg(ERR_MEMORY, 1);
	bridge->ret = 0;
	bridge->n_cmds = 0;
	bridge->commands = NULL;
	bridge->redirect = NULL;
	return (bridge);
}
