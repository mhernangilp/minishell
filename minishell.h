/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:01:46 by gfernand          #+#    #+#             */
/*   Updated: 2023/11/13 16:36:13 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define NORMAL 0
# define HEREDOC 1
# define APPEND 1
# define PARENT 0
# define CHILD 1
# define RETVAL 1
# define ERR_MEMORY "Error allocating memory\n"
# define ERR_PIPES "Error creating pipe\n"

# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <limits.h>
# include <sys/wait.h>
# include "libft.h"

# define ENTRADA_MS "\033[93mminishell > \033[0;0m"

extern char	**g_env;

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
/* SIGNALS */
void	heredoc_signals(void);
void	input_signals(void);
void	process_signals(void);

char	*worth_part(char *s);

///// EXECUTION /////

//execution.c
void	execution(t_bridge *bridge);
void	close_all(t_exec *exec);

//child_process.c
void	child_process(t_exec exec, int num);

//set_redirections.c
void	set_redirections(t_exec *exec, int num);

///// BUILTINS /////
//built_ins.c
int	is_parent_builtin(char *commands);
int	is_builtin(char *commands);
void	builtins(char **commands, int type);

//cd.c
int	cd(char **commands);

//pwd.c
int	pwd(void);

//unset.c
int	unset(char **commands);
void	b_delete(char *key);

//export.c
int	b_export(char **commands);
void	add(char *str, int type);

//echo.c
int	echo(char **commands);

//exit.c
int	b_exit(char **commands, int type);

///// ENVIROMENT /////
//enviroment.c
int	env(void);
char	**dup_env(char **envp);
char	*getenv_value(char *key);
int	env_len(char **env);
void	free_env(char **env);

//return_val.c
void	set_ret_val(int val);
int	get_ret_val(void);

///// ERRORS /////
//errors.c
void	error_msg(char *msg, int val);
void	exit_msg(char *msg, int val);

//// LIBFT /////
int	ft_atoi(const char *str);
char	*ft_itoa(int n);
char	**ft_split(const char *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int	ft_strncmp(char const *s1, char const *s2, size_t n);
size_t	ft_strlen(char const *str);
char	*ft_strdup(const char *src);
int	ft_isalpha(int c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);

//// HERE_DOC ////
void	load_heredoc(t_exec *exec, char *arg, int num);

#endif
