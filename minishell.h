#ifndef MINISHELL_H
# define MINISHELL_H


# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

void    rl_replace_line(const char *text, int clear_undo);
int     ft_strcmp(char *str, char *cmp);

#endif
