/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:12:02 by gfernand          #+#    #+#             */
/*   Updated: 2023/11/01 17:24:57 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void	data_struct(t_parse *parse, t_bdg *bridge, int i);
static void	select_file_and_type(t_parse *parse, t_bdg *bridge, int i);
static void	start_variables(t_parse *parse, t_bdg *bridge, char **s, int i);

char	**fill_redirections(t_parse *parse, t_bdg *bridge, char **s)
{
	int		i;
	int		j;

	i = -1;
	while (s[++i])
	{
		start_variables(parse, bridge, s, i);
		j = -1;
		while (s[i][++j])
		{
			if (s[i][j] == '"' || s[i][j] == '\'')
				j = quote(s[i], j);
			if (s[i][j] == '<' || s[i][j] == '>')
			{
				parse->start_rdir = j;
				j = take_redirection(parse, s, i, j) - 1;
				s = cut_rdir_in_cmds(parse, s, i, j);
				select_file_and_type(parse, bridge, i);
			}
		}
	}
	bridge->redirect[i].inred = NULL;
	bridge->redirect[i].outred = NULL;
	return (s);
}

static void	start_variables(t_parse *parse, t_bdg *bridge, char **s, int i)
{
	parse->n_ip = 0;
	parse->n_op = 0;
	count_redirections(parse, s[i]);
	data_struct(parse, bridge, i);
	parse->locate_ip_dir = -1;
	parse->locate_op_dir = -1;
}

static void	data_struct(t_parse *parse, t_bdg *bridge, int i)
{
	int	ip;
	int	op;

	ip = parse->n_ip;
	op = parse->n_op;
	if (parse->n_ip)
	{
		bridge->redirect[i].inred = (t_red *)malloc(sizeof(t_red));
		bridge->redirect[i].inred->file = ft_calloc(sizeof(char *), ip + 1);
		bridge->redirect[i].inred->type = malloc (sizeof(int) * ip);
		bridge->redirect[i].inred->num = ip;
	}
	else
		bridge->redirect[i].inred = NULL;
	if (parse->n_op)
	{
		bridge->redirect[i].outred = (t_red *)malloc(sizeof(t_red));
		bridge->redirect[i].outred->file = ft_calloc(sizeof(char *), op + 1);
		bridge->redirect[i].outred->type = malloc (sizeof(int) * op);
		bridge->redirect[i].outred->num = op;
	}
	else
		bridge->redirect[i].outred = NULL;
}

static void	select_file_and_type(t_parse *parse, t_bdg *bridge, int i)
{
	int	p;

	parse->rdirect = environments(parse, parse->rdirect);
	if (parse->rdirect[0] == '<')
	{
		p = ++parse->locate_ip_dir;
		if (parse->rdirect[1] != '<')
			bridge->redirect[i].inred->type[p] = NORMAL;
		else
			bridge->redirect[i].inred->type[p] = HEREDOC;
		parse->rdirect = worth_part(parse->rdirect);
		parse->rdirect = remove_quotes(parse->rdirect);
		bridge->redirect[i].inred->file[p] = parse->rdirect;
	}
	else if (parse->rdirect[0] == '>')
	{
		p = ++parse->locate_op_dir;
		if (parse->rdirect[1] != '>')
			bridge->redirect[i].outred->type[p] = NORMAL;
		else
			bridge->redirect[i].outred->type[p] = APPEND;
		parse->rdirect = worth_part(parse->rdirect);
		parse->rdirect = remove_quotes(parse->rdirect);
		bridge->redirect[i].outred->file[p] = parse->rdirect;
	}
}
