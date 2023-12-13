/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:37:28 by mhernang          #+#    #+#             */
/*   Updated: 2023/11/30 16:12:22 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	read_heredoc(t_exec *exec, int num);
static char	*get_here_arg(t_red *red, int number);

void	load_heredoc(t_exec *exec)
{
	int	i;

	i = -1;
	while (++i < exec -> bridge -> n_cmds)
		if (exec -> here[i].count)
			read_heredoc(exec, i);
}

int	count_heredocs(t_red *red)
{
	int	count;
	int	i;

	if (!red)
		return (0);
	i = -1;
	count = 0;
	while (++i < red -> num)
		if (red -> type[i] == HEREDOC)
			count++;
	return (count);
}

static void	read_heredoc(t_exec *exec, int num)
{
	int		i;
	char	*buf;
	char	*arg;

	heredoc_signals();
	i = -1;
	while (++i < exec -> here[num].count)
	{
		arg = get_here_arg(exec -> bridge -> redirect[num].inred, i + 1);
		buf = readline("heredoc> ");
		while (buf && global.signal == 0)
		{
			if (!ft_strncmp(arg, buf, ft_strlen(arg) + 1))
				break ;
			if (i == exec -> here[num].count - 1)
			{
				write(exec -> here[num].here_pipe[1], buf, ft_strlen(buf));
				write(exec -> here[num].here_pipe[1], "\n", 1);
			}
			free(buf);
			buf = readline("heredoc> ");
		}
		free(buf);
	}
	close(exec -> here[num].here_pipe[1]);
}

static char	*get_here_arg(t_red *red, int number)
{
	int	i;

	i = -1;
	while (number && ++i < red -> num)
	{
		if (red -> type[i] == HEREDOC)
			number--;
	}
	return (red -> file[i]);
}
