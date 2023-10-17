/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:00:54 by gfernand          #+#    #+#             */
/*   Updated: 2023/10/16 15:05:06 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int  special_caracter(char *input, int i);
static int	spaces_inside(char *input, char c);
static int	putreturn(char c, int nb_c);

int	check_rps(char *input, char c)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (!special_caracter(input, i))
			return (0);
		if (input[i] == '"' || input[i] == '\'')
		{
			i = quote(input, i);
			if (i == -1)
				return (putreturn('\'', 1));
			else if (i == -2)
				return (putreturn('"', 1));
		}
		if ((input[i] == c && input[i + 1] == c) || input[0] == c)
		{
			if (input[i + 2] == c && input[i + 3] == c)
				return (putreturn(c, 2));
			else if ((input[i + 2] == c || input[0] == c) && c != '|')
				return (putreturn(c, 1));
			else if (c == '|')
				return (putreturn(c, 1));
		}
	}
	return (spaces_inside(input, c));
}

static int  special_caracter(char *input, int i)
{
	if (input[i] == ';')
		return (putreturn(';', 1));
	else if (input[i] == '\\')
		return (putreturn('\\', 1));
	else
		return (1);
}

static int	spaces_inside(char *input, char c)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
			i = quote(input, i);
		if (input[i] == c || (input[i] == ' ' && i == 0))
		{
			i++;
			while (input[i] && (input[i] == ' ' || input[i] == '\t'))
				i++;
			if (!input[i] || (input[i] == c && input[i - 1] != c))
				return (putreturn(c, 1));
			if (input[i] == '\'' || input[i] == '"')
				i--;
		}
		if (input[i] != c)
			i++;
	}
	return (1);
}

static int	putreturn(char c, int nb_c)
{
	if (nb_c == 1)
		printf("syntax error near unexpected token `%c'\n", c);
	else
		printf("syntax error near unexpected token `%c%c'\n", c, c);
	return (0);
}
