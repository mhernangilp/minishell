/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:49:17 by gfernand          #+#    #+#             */
/*   Updated: 2023/10/09 14:13:14 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**ft_word(char **str, const char *s, char c, int count);

char	**split_quote(const char *s, char c)
{
	int		i;
	int		count;
	char	**str;

	i = 0;
	count = 1;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			i = quote(s, i);
			if (i < 0)
				return (NULL);
		}
		if (s[i] == c && s[i + 1] != c && s[i + 1])
				count++;
	}
	if (s[0] == c || s[0] == '\0')
		count--;
	str = (char **)malloc(sizeof(char *) *(count + 1));
	if (!str)
		return (NULL);
	ft_word(str, s, c, count);
	return (str);
}

static char	**ft_word(char **str, const char *s, char c, int count)
{
	int	i;
	int	found;
	int	start;

	i = 0;
	found = 1;
	while (found <= count)
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
			{
				if (s[i] == '"' || s[i] == '\'')
					i = quote(s, i);
				else
					i++;
			}
			str[found - 1] = ft_substr(s, start, (i - start));
			if (str == NULL)
				return (ft_splitfree(str));
			found++;
		}
		else
			i++;
	}
	str[found - 1] = NULL;
	return (str);
}

int	quote(const char *s, int i)
{
	int	quote;

	quote = 0;
	if (s[i] == '\'')
		quote = 1;
	else
		quote = 2;
	while (s[++i] && quote)
	{
		if ((s[i] == '\'' && quote == 1) || (s[i] == '"' && quote == 2))
			quote = 0;
	}
	if (quote == 1)
		return (-1);
	else if (quote == 2)
		return (-2);
	return (i);
}

char	*remove_matched_quotes(const char *s)
{
	char	*result;
	int		i;
	int		j;
	int		inside_quotes;

	result = (char *)malloc(ft_strlen(s) + 1);
	if (result == NULL)
		putexit("Error de memoria\n");
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
	result[ft_strlen(s)] = '\0';
	free((char *) s);
	return (result);
}
