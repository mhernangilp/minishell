/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:37:28 by mhernang          #+#    #+#             */
/*   Updated: 2023/11/26 18:37:31 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	load_heredoc(t_exec *exec, char *arg, int num)
{
	char	*buf;
	pid_t	pid;
	int	fd[2];

	if (pipe(fd) < 0)
		error_msg("Error creating pipe", 1);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		buf = readline("heredoc> ");
		while (buf)
		{
			if (!ft_strncmp(arg, buf, ft_strlen(arg) + 1))
				break ;
			write(fd[1], buf, ft_strlen(buf));
			write(fd[1], "\n", 1);
			free(buf);
			buf = readline("heredoc> ");
		}
		close(fd[1]);
		free(buf);
		exit(0);
	}
	else
	{
		close(fd[1]);
		exec -> in_out[num][0] = fd[0];
		waitpid(pid, NULL, 0);
	}
}
