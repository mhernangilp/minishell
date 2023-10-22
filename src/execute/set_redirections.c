/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:10:56 by mhernang          #+#    #+#             */
/*   Updated: 2023/10/22 19:09:31 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	in_red(t_exec *exec, int num);
static void	out_red(t_exec *exec, int num);
static void	set_pipes(t_exec *exec, int num);

void	set_redirections(t_exec *exec, int num)
{
	if (exec -> bridge -> redirect[num][0])
		in_red(exec, num);
	else if (exec -> bridge -> redirect[num][1])
		printf("Heredoc >\n");
		//load_heredoc();
	if (exec -> bridge -> redirect[num][2])
		out_red(exec, num);
	set_pipes(exec, num);
}

static void	set_pipes(t_exec *exec, int num)
{
	if (num != 0)
		if (exec -> in_out[num][0] == -1)
			dup2(exec -> pipe[num - 1][0], 0);
	if (num != (exec -> bridge -> n_cmds - 1))
		if (exec -> in_out[num][1] == -1)
			dup2(exec -> pipe[num][1], 1);
}

static void	in_red(t_exec *exec, int num)
{
	exec -> in_out[num][0] = open(exec -> bridge -> redirect[num][0], O_RDONLY);
	if (exec -> in_out[num][0] < 0)
		error_msg("Error infile");
	dup2(exec -> in_out[num][0], 0);
}

static void	out_red(t_exec *exec, int num)
{
	if (ft_atoi(exec -> bridge -> redirect[num][3]) == 0)
		exec -> in_out[num][1] = open(exec -> bridge -> redirect[num][2], O_CREAT
			| O_WRONLY | O_TRUNC, 0666);
	else if (ft_atoi(exec -> bridge -> redirect[num][3]) == 1)
		exec -> in_out[num][1] = open(exec -> bridge -> redirect[num][2], O_CREAT
			| O_WRONLY | O_APPEND, 0666);
	else 
		error_msg("Error with outfile redirection mode");
	if (exec -> in_out[num][1] < 0)
		error_msg("Error outfile");
	dup2(exec -> in_out[num][1], 1);
}
