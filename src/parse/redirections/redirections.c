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

static void	data_struct(t_parse *parse, t_bridge *bridge, int i);
static void	redirect_struct(t_parse *parse, t_bridge *bridge, int i);
static void	start_variables(t_parse *parse, t_bridge *bridge, char **s, int i);

char	**fill_redirections(t_parse *parse, t_bridge *bridge, char **s)
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
				if (s[i][j] == '<')
					parse->locate_ip_dir++;
				else
					parse->locate_op_dir++;
				parse->start_rdir = j;
				j = malloc_redirect(parse, s, i, j) - 1;
				s = out_redirect(parse, s, i, j);
				redirect_struct(parse, bridge, i);
			}
		}
	}
	printf("TEEEE-%s-\n", bridge->redirect[0].inred->file[0]);
	/*i = -1;
	while (bridge->redirect[++i].inred)
	{
		j = -1;
		while (bridge->redirect[i].inred->file[++j])
			printf("PRUEBA-%s-\n", bridge->redirect[i].inred->file[j]);
	}*/
	return (s);
}

static void	start_variables(t_parse *parse, t_bridge *bridge, char **s, int i)
{
		parse->n_ip = 0;
		parse->n_op = 0;
		count_redirections(parse, s[i]);
		data_struct(parse, bridge, i);
		parse->locate_ip_dir = -1;
		parse->locate_op_dir = -1;
}

static void	data_struct(t_parse *parse, t_bridge *bridge, int i)
{
	if (parse->n_ip)
	{
		bridge->redirect[i].inred = (t_red *)malloc(sizeof(t_red));
		bridge->redirect[i].inred->file = malloc (sizeof(char *) * parse->n_ip + 1);
		bridge->redirect[i].inred->type = malloc (sizeof(int) * parse->n_ip);
		bridge->redirect[i].inred->num = parse->n_ip;
		printf("KJN%d\n", parse->n_ip);
	}
	else
		bridge->redirect[i].inred = NULL;
	if (parse->n_op)
	{
		bridge->redirect[i].outred = (t_red *)malloc(sizeof(t_red));
		bridge->redirect[i].outred->file = malloc (sizeof(char *) * parse->n_op + 1);
		bridge->redirect[i].outred->type = malloc (sizeof(int) * parse->n_op);
		bridge->redirect[i].outred->num = parse->n_op;
	}
	else
		bridge->redirect[i].outred = NULL;
}

static void	redirect_struct(t_parse *parse, t_bridge *bridge, int i)
{
	int	ip;
	int	op;

	ip = parse->locate_ip_dir;
	op = parse->locate_op_dir;
	parse->rdirect = remove_quotes(parse->rdirect);
	if (parse->rdirect[0] == '<')
	{
		if (parse->rdirect[1] != '<')
			bridge->redirect[i].inred->type[ip] = NORMAL;
		else
			bridge->redirect[i].inred->type[ip] = HEREDOC;
		parse->rdirect = remove_redirection(parse->rdirect);
		bridge->redirect[i].inred->file[ip] = parse->rdirect;
		printf("%d-%i\n", i, ip);
		//bridge->redirect[i].inred->file[ip + 1] = NULL;
		printf("REDIR INPUT-%s-\n", bridge->redirect[i].inred->file[ip]);
	}
	else if (parse->rdirect[0] == '>')
	{
		if (parse->rdirect[1] != '>')
			bridge->redirect[i].outred->type[op] = NORMAL;
		else
			bridge->redirect[i].outred->type[op] = APPEND;
		parse->rdirect = remove_redirection(parse->rdirect);
		bridge->redirect[i].outred->file[op] = parse->rdirect;
		//bridge->redirect[i].outred->file[op + 1] = NULL;
		printf("REDIR OUTPUT-%s-\n", bridge->redirect[i].outred->file[op]);
	}
	free (parse->rdirect);
}
