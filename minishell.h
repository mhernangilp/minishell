/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:01:46 by gfernand          #+#    #+#             */
/*   Updated: 2023/10/15 17:22:28 by mhernang         ###   ########.fr       */
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
	char	*here_doc;
	char	*outfile;
	int	out_mode;
	char	***commands;
	int	ncommands;
} t_bridge;

typedef struct s_exec
{
	pid_t		*pid;
	int			**pipe;
	int			in;
	int			out;
	char		**paths;
	t_bridge	*bridge;
}	t_exec;

typedef struct	s_parse
{
	char	***str_space;
	int	commands;
}	t_parse;

void	rl_replace_line(const char *text, int clear_undo);
void	putexit(char *s);

/* PARSE */
void	start_parse(t_parse *parse, char *input);

///// EXECUTION /////

//execution.c
void	execution(t_bridge *bridge);
void	close_all(t_exec *exec);

//child_process.c
void	child_process(t_exec exec, int num);

//set_redirections.c
void	set_redirections(t_exec *exec, int num);

///// ERRORS /////
//errors.c
void	error_msg(char *msg);

///// TEST EXECUTION /////
//test_execution.c
t_bridge	*test_execution();

#endif
