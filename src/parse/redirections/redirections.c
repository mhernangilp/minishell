/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:12:02 by gfernand          #+#    #+#             */
/*   Updated: 2023/10/30 14:12:08 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void	data_struct(t_parse *parse, t_bridge *bridge, int i);
static void	redirect_struct(t_parse *parse, t_bridge *bridge, int i);

char	**fill_redirections(t_parse *parse, t_bridge *bridge, char **s)
{
	int		i;
	int		j;

	parse->n_ip = 0;
	parse->n_op = 0;
	i = -1;
	while (s[++i])
	{
		count_redirections(parse, s[i]);
		data_struct(parse, bridge, i);
		j = -1;
		while (s[i][++j])
		{
			if (s[i][j] == '"' || s[i][j] == '\'')
				j = quote(s[i], j);
			if (s[i][j] == '<' || s[i][j] == '>')
			{
				parse->start_rdir = j;
				j = malloc_redirect(parse, s, i, j) - 1;
				s = out_redirect(parse, s, i, j);
				redirect_struct(parse, bridge, i);
			}
		}
	}
	return (s);
}

static void	data_struct(t_parse *parse, t_bridge *bridge, int i)
{
	if (parse->n_ip)
	{
		bridge->redirect[i].inred = (t_red *)malloc(sizeof(t_red));
		bridge->redirect[i].inred->file = malloc (sizeof(char *) * parse->n_ip + 1);
		bridge->redirect[i].inred->type = malloc (sizeof(int) * parse->n_ip);
		bridge->redirect[i].inred->num = parse->n_ip;
	}
	if (parse->n_op)
	{
		bridge->redirect[i].outred = (t_red *)malloc(sizeof(t_red));
		bridge->redirect[i].outred->file = malloc (sizeof(char *) * parse->n_ip + 1);
		bridge->redirect[i].outred->type = malloc (sizeof(int) * parse->n_ip);
		bridge->redirect[i].outred->num = parse->n_ip;
	}
}

static void	redirect_struct(t_parse *parse, t_bridge *bridge, int i)
{
	parse->rdirect = remove_quotes(parse->rdirect);
	if (parse->rdirect[0] == '<')
	{
		bridge->redirect[i].inred->file[0] = parse->rdirect;
		if (parse->rdirect[1] != '<')
			bridge->redirect[i].inred->type[0] = NORMAL;
		else
			bridge->redirect[i].inred->type[0] = HEREDOC;
	}
	else if (parse->rdirect[0] == '>')
	{
		bridge->redirect[i].outred->file[0] = parse->rdirect;
		if (parse->rdirect[1] != '>')
			bridge->redirect[i].outred->type[0] = NORMAL;
		else
			bridge->redirect[i].outred->type[0] = APPEND;
	}
	free (parse->rdirect);
}
