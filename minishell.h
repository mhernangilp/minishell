/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:01:46 by gfernand          #+#    #+#             */
/*   Updated: 2023/11/05 18:07:11 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define NORMAL 0
# define HEREDOC 1
# define APPEND 1

# include <dirent.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include "libft.h"

# define ENTRADA_MS "\033[93mminishell > \033[0;0m"

extern int	g_ret_val;

typedef struct s_red
{
	int		num;
	char	**file;
	int		*type;
}	t_red;

typedef struct s_cmdred
{
	t_red	*inred;
	t_red	*outred;
}	t_cmdred;

typedef struct s_bridge
{
	t_cmdred	*redirect;
	char		***commands;
	int			n_cmds;
}	t_bridge;

typedef struct s_exec
{
	pid_t		*pid;
	int			**pipe;
	int			**in_out;
	char		**paths;
	char		**envp;
	t_bridge	*bridge;
}	t_exec;

typedef struct s_parse
{
	char	**env;
	char	*r_env;
	int		nb_env;
	int		l_d;
	int		a;
	char	*rdirect;
	int		start_rdir;
	int		n_ip;
	int		n_op;
	int		locate_ip_dir;
	int		locate_op_dir;
}	t_parse;

void	rl_replace_line(const char *text, int clear_undo);
void	putexit(char *s);

/* PARSE */
t_bridge	*start_parse(char *input);
int		check_rps(char *input, char c);
int		check_input(char *input);
char	**split_quote(const char *s, char c);
int		quote(const char *s, int i);
char	*remove_quotes(const char *s);
/* ENV */
char	*environments(t_parse *parse, char *s);
int		count_env(char *s);
char	*cut_and_get_env(t_parse *parse, char *s, int i);
int		env_to_str(t_parse *parse, char *s, int i, int e);
int		type_of_quote(char *str, int i, int quote);
/* REDIRECTIONS */
char	**fill_redirections(t_parse *parse, t_bridge *bridge, char **s);
void	count_redirections(t_parse *parse, char *s);
int		take_redirection(t_parse *parse, char **s, int i, int j);
char	**cut_rdir_in_cmds(t_parse *parse, char **s, int i, int j);
char	*worth_part(char *s);

///// EXECUTION /////

//execution.c
void	execution(t_bridge *bridge, char **envp);
void	close_all(t_exec *exec);

//child_process.c
void	child_process(t_exec exec, int num);

//set_redirections.c
void	set_redirections(t_exec *exec, int num);

///// ERRORS /////
//errors.c
void	error_msg(char *msg);

//// LIBFT /////
char	**ft_split(const char *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);

//// HERE_DOC ////
void	load_heredoc(t_exec *exec, char *arg, int num);

///// TEST EXECUTION /////
//test_execution.c
t_bridge		*test_execution();
t_bridge		*test_execution2();
t_bridge		*test_execution3();
t_bridge		*test_execution4();

#endif
