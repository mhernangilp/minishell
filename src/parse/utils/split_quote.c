/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:49:17 by gfernand          #+#    #+#             */
/*   Updated: 2023/10/16 15:13:31 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static char	**ft_word(char **str, const char *s, char c, int count);
static int	count_inside_quotes(const char *s, char c, int i);

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
		if (s[i] && s[i + 1] && s[i] == c && s[i + 1] != c)
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
			i = count_inside_quotes(s, c, i);
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

static int	count_inside_quotes(const char *s, char c, int i)
{
	while (s[i] && s[i] != c)
	{
		if (s[i] == '"' || s[i] == '\'')
			i = quote(s, i);
		i++;
	}
	return (i);
}

int	quote(const char *s, int i)
{
	int	quote;

	quote = 0;
	if (s[i] == '\'')
		quote = 1;
	else
		quote = 2;
	while (quote && s[++i])
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
