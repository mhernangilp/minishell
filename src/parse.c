/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:59:05 by gfernand          #+#    #+#             */
/*   Updated: 2023/10/17 18:27:12 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_parse_struct(t_parse *parse);
static char	*cut_and_get_env(char *str, int i);
static char	*environments(char *str);

void	start_parse(char *input)
{
	t_parse	*parse;
	char	**str_pipe;
	int		i;
	int		j;

	parse = malloc (sizeof (t_parse));
	init_parse_struct(parse);
	if (!check_rps(input, '|') || !check_rps(input, '<') || !check_rps(input, '>'))
		return ;
	str_pipe = split_quote(input, '|');
	while (str_pipe[parse->ncommands])
		parse->ncommands++;
	printf("commands %d\n", parse->ncommands);
	parse->command = ((char ***) malloc (sizeof (char **) * (parse->ncommands + 1)));
	parse->command[parse->ncommands] = NULL;
	i = -1;
	while (str_pipe[++i] && str_pipe[i][0])
	{
		parse->command[i] = split_quote(str_pipe[i], ' ');
		printf("%d PIPE - %s\n", i, str_pipe[i]);
		j = -1;
		while (parse->command[i][++j] && parse->command[i][j][0])
		{
			parse->command[i][j] = environments(parse->command[i][j]);
			parse->command[i][j] = remove_matched_quotes(parse->command[i][j]);
			printf("----SPACE %d- %s\n", j, parse->command[i][j]);
		}
	}
	ft_splitfree(str_pipe);
	i = -1;
	while (parse->command[++i])
		ft_splitfree(parse->command[i]);
	free(parse->command);
	free(parse);
}

/*
 *	redirecciones (<, <<, >, >>, |)
 *
 *	expansion de variables ($PATH, $USER...)
 *
 * */

static char	*environments(char *str)
{
	char	**env;
	int		count_env;
	int		i;
	int		j;

	i = -1;
	count_env = 0;
	while (str[++i])
	{
		if (str[i] == '\'')
			i = quote(str, i);
		else if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '.')
			count_env++;
	}
	if (count_env == 0)
		return (str);
	env = (char **)malloc (sizeof (char *) * (count_env + 1));
	i = -1;
	j = -1;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '.')
		{
			env[++j] = cut_and_get_env(str, i);
			printf("ENV --> %s\n", env[j]);
		}
	}
	env[++j] = NULL;
//	ft_splitfree(env);
	return (str);
}

static char	*cut_and_get_env(char *str, int i)
{
	char	*env;
	char	*aux;
	int		start;

	start = ++i;
	while (str[i] && str[i] != '\'' && str[i] != '"' && str[i] != ' ' && str[i] != '\t')
		i++;
	aux = ft_substr(str, start, i - start);
	env = getenv(aux);
	free (aux);
	return (env);
}

static void	init_parse_struct(t_parse *parse)
{
	parse->ncommands = 0;
	parse->command = NULL;
}
