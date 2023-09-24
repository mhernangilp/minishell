#ifndef MINISHELL_H
# define MINISHELL_H


# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>


# define ENTRADA_MS "\001\033[93m\002minishell > \001\033[0;0m\002"

void    rl_replace_line(const char *text, int clear_undo);
void    builtins(char *input);
int     ft_strcmp(char *str, char *cmp);


#endif
