/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:29:43 by gfernand          #+#    #+#             */
/*   Updated: 2023/11/01 17:22:59 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	count_redirections(t_parse *parse, char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '"' || s[i] == '\'')
			i = quote(s, i);
		if (s[i] == '<')
		{
			if (s[i + 1] == '<' || s[i + 1] == '>')
				i++;
			parse->n_ip++;
		}
		if (s[i] == '>')
		{
			if (s[i + 1] == '>')
				i++;
			parse->n_op++;
		}
	}
}

int	take_redirection(t_parse *parse, char **s, int i, int j)
{
	if (s[i][j + 1] == '<' || s[i][j + 1] == '>')
		j += 2;
	else
		j++;
	while (s[i][j] == ' ' || s[i][j] == '\t')
		j++;
	while (s[i][j] && s[i][j] != ' ' && s[i][j] != '\t' && s[i][j] != '<'
				&& s[i][j] != '>')
	{
		if (s[i][j] == '\'' || s[i][j] == '"')
			j = quote(s[i], j);
		j++;
	}
	parse->rdirect = ft_substr(s[i], parse->start_rdir, j - parse->start_rdir);
	return (j);
}

char	**cut_rdir_in_cmds(t_parse *parse, char **s, int i, int j)
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

char	*worth_part(char *s)
{
	char	*result;
	int		i;
	int		start;

	result = NULL;
	i = -1;
	if (s[++i])
	{
		i++;
		if (s[i] == '<' || s[i] == '>')
			i++;
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
				i++;
		start = i;
		i = ft_strlen(s);
		result = ft_substr(s, start, i - start);
	}
	free (s);
	return (result);
}
