/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:57:27 by gfernand          #+#    #+#             */
/*   Updated: 2023/10/16 15:41:29 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static char	*malloc_quotes(const char *s);

char	*remove_quotes(const char *s)
{
	char	*result;
	int		i;
	int		j;
	int		inside_quotes;

	result = malloc_quotes(s);
	i = -1;
	j = -1;
	inside_quotes = 0;
	while (s[++i])
	{
		if (s[i] == '\'' && !inside_quotes)
			inside_quotes = 1;
		else if (s[i] == '\'' && inside_quotes == 1)
			inside_quotes = 0;
		else if (s[i] == '"' && !inside_quotes)
			inside_quotes = 2;
		else if (s[i] == '"' && inside_quotes == 2)
			inside_quotes = 0;
		else
			result[++j] = s[i];
	}
	result[++j] = '\0';
	free((char *) s);
	return (result);
}

static char	*malloc_quotes(const char *s)
{
	char	*result;
	int		i;
	int		nb_quotes;
	int		inside_quotes;

	nb_quotes = 0;
	inside_quotes = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'' && !inside_quotes)
			inside_quotes = 1;
		else if (s[i] == '"' && !inside_quotes)
			inside_quotes = 2;
		else if ((s[i] == '\'' && inside_quotes == 1)
			|| (s[i] == '"' && inside_quotes == 2))
		{
			inside_quotes = 0;
			nb_quotes += 2;
		}
	}
	result = (char *)malloc(ft_strlen(s) + 1 - nb_quotes);
	if (result == NULL)
		putexit("Error de memoria\n");
	return (result);
}
