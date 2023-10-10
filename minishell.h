/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:01:46 by gfernand          #+#    #+#             */
/*   Updated: 2023/10/09 13:55:54 by gfernand         ###   ########.fr       */
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
	char	*infile;
	char	**here_doc;
	char	*outfile;
	int		out_mode;
	char	***commands;
	int		ncommands;
}	t_bridge;

typedef struct s_parse
{
	char	***command;
	int		ncommands;
}	t_parse;

void	rl_replace_line(const char *text, int clear_undo);
void	putexit(char *s);
int		putreturn(char c, int nb_c);

/* PARSE */
void	start_parse(t_parse *parse, char *input);
char	**split_quote(const char *s, char c);
int		quote(const char *s, int i);
char	*remove_matched_quotes(const char *s);

#endif
