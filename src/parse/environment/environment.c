/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:04:00 by gfernand          #+#    #+#             */
/*   Updated: 2023/10/30 11:04:03 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void	expand_variable(t_parse *parse, char *s);
static void	parse_env(t_parse *parse, char *s);
static void	get_env(t_parse *parse, char *s);

char	*environments(char *s)
{
	t_parse	*parse;

	parse = malloc (sizeof (t_parse));
	parse->nb_env = count_env(s);
	if (parse->nb_env == 0)
		return (s);
	parse->env = (char **)malloc (sizeof (char *) * (parse->nb_env + 1));
	if (!parse->env)
		putexit("Malloc error\n");
	get_env(parse, s);
	expand_variable(parse, s);
	free(parse->env);
	free(s);
	return (parse->r_env);
}

static	void	expand_variable(t_parse *parse, char *s)
{
	int	e_len;
	int	i;

	e_len = 0;
	i = -1;
	while (parse->env[++i])
		e_len += ft_strlen(parse->env[i]);
	e_len = e_len - parse->l_d + 1;
	parse->r_env = malloc (sizeof (char *) * (ft_strlen(s) + e_len));
	if (!parse->r_env)
		putexit("Malloc error\n");
	parse_env(parse, s);
}

static void	get_env(t_parse *parse, char *s)
{
	int	i;
	int	j;
	int	quote;

	parse->l_d = 0;
	i = -1;
	j = -1;
	quote = 0;
	while (s[++i])
	{
		quote = type_of_quote(s, i, quote);
		if (s[i] == '$' && s[i + 1] != ' ' && s[i + 1] != '.' && quote != 1)
			parse->env[++j] = cut_and_get_env(parse, s, i);
	}
	parse->env[++j] = NULL;
}

static void	parse_env(t_parse *parse, char *s)
{
	int	i;
	int	e;
	int	quote;

	parse->a = -1;
	i = -1;
	e = -1;
	quote = 0;
	while (s[++i])
	{
		quote = type_of_quote(s, i, quote);
		if (s[i] == '$' && s[i + 1] != ' ' && s[i + 1] != '.'
			&& s[i + 1] && quote != 1)
			i = env_to_str(parse, s, i, ++e);
		else
			parse->r_env[++parse->a] = s[i];
	}
	parse->r_env[++parse->a] = '\0';
}
