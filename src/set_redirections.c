/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:10:56 by mhernang          #+#    #+#             */
/*   Updated: 2023/10/15 19:07:09 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	in_red(t_exec *exec)
{
	exec -> in = open(exec -> bridge -> infile, O_RDONLY);
	if (exec -> in < 0)
		error_msg("Error infile");
	dup2(exec -> in, 0);
}

static void	out_red(t_exec *exec)
{
	if (exec -> bridge -> outfile)
	{
		if (exec -> bridge -> out_mode == 0)
			exec -> out = open(exec -> bridge -> outfile, O_CREAT
				| O_WRONLY | O_TRUNC, 0666);
		else
			exec -> out = open(exec -> bridge -> outfile, O_CREAT
				| O_WRONLY | O_APPEND, 0666);
	}
	if (exec -> out < 0)
		error_msg("Error outfile");
	dup2(exec -> out, 1);
}

void	set_redirections(t_exec *exec, int num)
{
	if (num == 0)
	{
		if (exec -> bridge -> infile)
			in_red(exec);
		else if (exec -> bridge -> here_doc)
			printf("Heredoc\n");
			//load_heredoc();
	}
	if (num == (exec -> bridge -> ncommands - 1))
		if (exec -> bridge -> outfile)
			out_red(exec);
}
