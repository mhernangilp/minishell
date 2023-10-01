/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:01:46 by gfernand          #+#    #+#             */
/*   Updated: 2023/09/26 14:03:22 by gfernand         ###   ########.fr       */
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
	int	out_mode;
	char	**commands;
	int	ncommands;
} t_bridge;

typedef struct	s_parse
{
	char	***str_space;
	int	commands;
}	t_parse;

void	rl_replace_line(const char *text, int clear_undo);
void	putexit(char *s);

/* PARSE */
void	check_pipes(t_parse *parse, char *input);

#endif
