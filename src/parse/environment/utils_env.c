/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:04:10 by gfernand          #+#    #+#             */
/*   Updated: 2023/10/30 11:04:13 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	count_env(char *s)
{
	int	i;
	int	count_env;
	int	doble_quote;

	i = -1;
	count_env = 0;
	doble_quote = 0;
	while (s[++i])
	{
		if (s[i] == '"' && doble_quote)
			doble_quote = 0;
		else if (s[i] == '"' && !doble_quote)
			doble_quote = 2;
		else if (s[i] == '\'' && !doble_quote)
			i = quote(s, i);
		else if (s[i] == '$' && s[i + 1] != ' ' && s[i + 1] != '.' && s[i + 1])
			count_env++;
	}
	return (count_env);
}

int	type_of_quote(char *str, int i, int quote)
{
	if (str[i] == '\'' && !quote)
		quote = 1;
	else if (str[i] == '"' && !quote)
		quote = 2;
	else if ((str[i] == '\'' && quote == 1) || (str[i] == '"' && quote == 2))
		quote = 0;
	return (quote);
}

char	*cut_and_get_env(t_parse *parse, char *s, int i)
{
	char	*env;
	char	*aux;
	int		start;

	start = ++i;
	while (s[i] != '\'' && s[i] != '"' && s[i] != ' ' && s[i] != '\t'
		&& s[i] && s[i] != '$')
		i++;
	parse->l_d += i - start + 1;
	aux = ft_substr(s, start, i - start);
	env = getenv_value(aux);
	free (aux);
	return (env);
}

int	env_to_str(t_parse *parse, char *s, int i, int e)
{
	int	j;

	if (parse->env[e])
	{
		j = -1;
		while (parse->env[e][++j])
			parse->r_env[++parse->a] = parse->env[e][j];
	}
	i++;
	while (s[i] && s[i] != '\'' && s[i] != '"'
		&& s[i] != ' ' && s[i] != '\t' && s[i] != '$')
		i++;
	return (i - 1);
}
