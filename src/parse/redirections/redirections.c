/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:12:02 by gfernand          #+#    #+#             */
/*   Updated: 2023/10/30 13:12:06 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	malloc_redirect(char **s, int i, int j);

void    fill_redirections(t_bridge *bridge, char **s)
{
	int	i;
	int	j;
    
	i = -1;
	while (s[++i])
	{
		j = -1;
		while (s[i][++j])
		{
			if (s[i][j] == '"' || s[i][j] == '\'')
				j = quote(s[i], j);
			if (s[i][j] == '<' || s[i][j] == '>')
				j = malloc_redirect(s, i, j) - 1;
		}
	}
	bridge->n_cmds = bridge->n_cmds + 2 - 1 - 1;
}

static int	malloc_redirect(char **s, int i, int j)
{
	int	m;
	char    *aux_redirect;

	m = j;
	if (s[i][j + 1] == '<' || s[i][j + 1] == '>')
		j += 2;
	else
		j++;
	while (s[i][j] == ' ' || s[i][j] == '\t')
		j++;
	while (s[i][j] && s[i][j] != ' ' && s[i][j] != '\t')
		j++;
	//bridge->redirect = ft_substr(s[i], m, j - m);
	aux_redirect = ft_substr(s[i], m, j - m);
	printf("REDIRECT ==%s\n", aux_redirect);
	free (aux_redirect);
	return (j);
}
