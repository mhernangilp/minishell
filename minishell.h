/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:01:46 by gfernand          #+#    #+#             */
/*   Updated: 2023/10/16 15:04:18 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

# define ENTRADA_MS "\033[93mminishell > \033[0;0m"

typedef struct s_bridge
{
	char	**redirect;
	char	***command;
	int		n_cmds;
}	t_bridge;

typedef struct s_parse
{
	char	**env;
	char	*r_env;
	int		nb_env;
	int		l_d;
	int		a;
}	t_parse;

void	rl_replace_line(const char *text, int clear_undo);
void	putexit(char *s);

/* PARSE */
void	start_parse(char *input);
int		check_rps(char *input, char c);
char	**split_quote(const char *s, char c);
int		quote(const char *s, int i);
char	*remove_quotes(const char *s);
/* ENV */
char	*environments(char *str);
int		count_env(char *s);
char	*cut_and_get_env(t_parse *parse, char *s, int i);
int		env_to_str(t_parse *parse, char *s, int i, int e);
int		type_of_quote(char *str, int i, int quote);

#endif
