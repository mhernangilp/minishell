/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:10:56 by mhernang          #+#    #+#             */
/*   Updated: 2023/11/30 16:06:05 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	in_red(t_exec *exec, int num);
static void	out_red(t_exec *exec, int num);
static void	set_pipes(t_exec *exec, int num);

void	set_redirections(t_exec *exec, int num)
{
	if (exec -> bridge -> redirect[num].inred)
		in_red(exec, num);
	if (exec -> bridge -> redirect[num].outred)
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
	int	i;

	i = -1;
	while (++i < exec -> bridge -> redirect[num].inred -> num)
	{
		if (exec -> bridge -> redirect[num].inred -> type[i] == NORMAL)
			exec -> in_out[num][0] = open(exec -> bridge -> redirect[num].inred
					-> file[i], O_RDONLY);
		else if (exec -> bridge -> redirect[num].inred -> type[i] == HEREDOC)
			exec -> in_out[num][0] = exec -> here[num].here_pipe[0];
		else
			error_msg("Error with infile redirection mode", 1);
		if (exec -> in_out[num][0] < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			error_msg(exec->bridge->redirect[num].inred->file[i], 1);
		}
	}
	dup2(exec -> in_out[num][0], 0);
}

static void	out_red(t_exec *exec, int num)
{
	int	i;

	i = -1;
	while (++i < exec -> bridge -> redirect[num].outred -> num)
	{
		if (exec -> bridge -> redirect[num].outred -> type[i] == NORMAL)
			exec -> in_out[num][1] = open(exec -> bridge -> redirect[num].outred
					-> file[i], O_CREAT | O_WRONLY | O_TRUNC, 0666);
		else if (exec -> bridge -> redirect[num].outred -> type[i] == APPEND)
			exec -> in_out[num][1] = open(exec -> bridge -> redirect[num].outred
					-> file[i], O_CREAT | O_WRONLY | O_APPEND, 0666);
		else
			error_msg("Error with outfile redirection mode", 1);
		if (exec -> in_out[num][1] < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			error_msg(exec->bridge->redirect[num].outred->file[i], 1);
		}
	}
	dup2(exec -> in_out[num][1], 1);
}
