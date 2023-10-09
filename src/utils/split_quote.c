/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:49:17 by gfernand          #+#    #+#             */
/*   Updated: 2023/10/09 14:02:44 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**ft_word(char **str, const char *s, char c, int count);
static int	quote(const char *s, int i);
static char	**ft_free(char **str);

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

static int	quote(const char *s, int i)
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
	if (quote)
		return (-1);
	return (i);
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
				return (ft_free(str));
			found++;
		}
		else
			i++;
	}
	str[found - 1] = NULL;
	return (str);
}

static char	**ft_free(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}
