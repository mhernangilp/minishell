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

static int	malloc_redirect(t_parse *parse, char **s, int i, int j);
static char	**out_redirect(t_parse *parse, char **s, int i, int j);

char	**fill_redirections(t_parse *parse, t_bridge *bridge, char **s)
{
	int		i;
	int		j;

	parse->nb_rdir = 0;
	i = -1;
	while (s[++i])
	{
		//count_redirections(parse, s[i]);
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
				//redirect_struct(parse, bridge, i);
			}
		}
	}
	(void) bridge;
	return (s);
}
/*
static void	redirect_struct(t_parse *parse, t_bridge *bridge, int i)
{
	parse->rdirect = remove_quotes(parse->rdirect);
	if (parse->rdirect[0] == '<')
	{
		bridge->redirect[i].inred = (t_red *)malloc(sizeof(t_red));
		bridge->redirect[i].inred->num = 1;
		bridge->redirect[i].inred->file = malloc (sizeof(char *) * );
		bridge->redirect[i].inred->file[0] = parse->rdirect;
		bridge->redirect[i].inred->type = (int *)malloc(1 * sizeof(int));
		if (parse->rdirect[1] != '<')
			bridge->redirect[i].inred->type[0] = NORMAL;
		else
			bridge->redirect[i].inred->type[0] = HEREDOC;
		bridge->redirect[i].outred = NULL;
		bridge->redirect->inred->num++;
	}
	else if (parse->rdirect[0] == '>')
	printf("NUM-> %d\n", bridge->redirect->inred.num);
	free (parse->rdirect);
}

static void	count_redirections(t_parse *parse, char *s)
{
}*/

static int	malloc_redirect(t_parse *parse, char **s, int i, int j)
{

	if (s[i][j + 1] == '<' || s[i][j + 1] == '>')
		j += 2;
	else
		j++;
	while (s[i][j] == ' ' || s[i][j] == '\t')
		j++;
	while (s[i][j] && s[i][j] != ' ' && s[i][j] != '\t' && s[i][j] != '<'
				&& s[i][j] != '>')
		j++;
	parse->rdirect = ft_substr(s[i], parse->start_rdir, j - parse->start_rdir);
	printf("%d REDIRECT->%s\n", i, parse->rdirect);
	return (j);
}

static char	**out_redirect(t_parse *parse, char **s, int i, int j)
{
	int	m;

	m = parse->start_rdir;
	while (s[i][m] && m <= j)
	{
		s[i][m] = ' ';
		m++;
	}
	return (s);
}
