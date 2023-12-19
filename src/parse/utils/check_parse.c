/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:00:54 by gfernand          #+#    #+#             */
/*   Updated: 2023/12/19 17:07:29 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	special_caracter(t_bridge *bridge, char *input, int i);
static int	spaces_inside(t_bridge *bridge, char *input, char c);
static int	putreturn(t_bridge *bridge, char c, int nb_c);

int	check_input(char *input)
{
	int	i;

	if (!input || !input[0])
		return (0);
	i = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
	{
		i++;
		if (!input[i])
			return (0);
	}
	return (1);
}

int	check_rps(t_bridge *bridge, char *input, char c)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (!special_caracter(bridge, input, i))
			return (0);
		if (input[i] == '"' || input[i] == '\'')
		{
			i = quote(input, i);
			if (i == -1)
				return (putreturn(bridge, '\'', 1));
			else if (i == -2)
				return (putreturn(bridge, '"', 1));
		}
		if ((input[i] == c && input[i + 1] == c) || (input[0] == c && c == '|'))
		{
			if (input[i + 2] == c && input[i + 3] == c)
				return (putreturn(bridge, c, 2));
			else if (input[i + 2] == c || c == '|')
				return (putreturn(bridge, c, 1));
		}
	}
	return (spaces_inside(bridge, input, c));
}

static int	special_caracter(t_bridge *bridge, char *input, int i)
{
	if (input[0] == '|' && input[1] == '\0')
		return (putreturn(bridge, '|', 1));
	if (input[i] == '<' || input[i] == '>')
	{
		if (input[i] == '>' && input[i + 1] == '<')
			return (putreturn(bridge, '<', 1));
		if (input[i + 1] == '<' || input[i + 1] == '>')
		{
			if (input[i + 2] && input[i + 2] == '<')
				return (putreturn(bridge, '<', 1));
			if (input[i + 2] && input[i + 2] == '>')
				return (putreturn(bridge, '>', 1));
		}
	}
	if (input[i] == ';')
		return (putreturn(bridge, ';', 1));
	else if (input[i] == '\\')
		return (putreturn(bridge, '\\', 1));
	else
		return (1);
}

static int	spaces_inside(t_bridge *bridge, char *input, char c)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == c || (input[i] == ' ' && i == 0 && c != '<'))
		{
			i++;
			while (input[i] && (input[i] == ' ' || input[i] == '\t'))
				i++;
			if (!input[i] || (input[i] == c && input[i - 1] != c))
				return (putreturn(bridge, c, 1));
		}
		if (input[i] == '"' || input[i] == '\'')
			i = quote(input, i);
		if (input[i] != c)
			i++;
	}
	return (1);
}

static int	putreturn(t_bridge *bridge, char c, int nb_c)
{
	if (nb_c == 1)
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putchar_fd(c, 2);
		ft_putstr_fd("'\n", 2);
	}
	else
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putchar_fd(c, 2);
		ft_putchar_fd(c, 2);
		ft_putstr_fd("'\n", 2);
	}
	set_ret_val(bridge, 258);
	return (0);
}
