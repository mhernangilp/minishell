/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:02:26 by gfernand          #+#    #+#             */
/*   Updated: 2023/12/26 20:36:08 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**minishell(char **m_env);
static void	free_commands(t_bdg *bridge);
static void	free_redirect(t_bdg *bridge, int i);
static void	exit_input(void);

int	g_signal;

int	main(int argc, char **argv, char **envp)
{
	char	**m_env;

	(void) argv;
	if (argc != 1)
		exit_msg("Wrong parameters\n", 1);
	m_env = dup_env(envp);
	add(&m_env, "?=0", RETVAL);
	b_delete(&m_env, "OLDPWD");
	ctr();
	while (1)
		m_env = minishell(m_env);
	return (0);
}

static char	**minishell(char **m_env)
{
	t_bdg	*bridge;
	char	*input;

	g_signal = 0;
	bridge = NULL;
	input_signals();
	input = readline(ENTRADA_MS);
	if (input == NULL)
		exit_input();
	if (*input)
	{
		add_history(input);
		bridge = start_parse(input, m_env);
		if (bridge != NULL && bridge->ret == 0)
			execution(bridge);
	}
	if (bridge)
		m_env = bridge -> m_env;
	free(input);
	free_commands(bridge);
	return (m_env);
}

static void	exit_input(void)
{
	ft_putstr_fd("\033[1A\033[2K", 1);
	ft_putstr_fd(ENTRADA_MS, 1);
	ft_putstr_fd("exit\n", 1);
	exit(0);
}

static void	free_commands(t_bdg *bridge)
{
	int	i;

	if (!bridge)
		return ;
	if (bridge->ret != -1)
	{
		i = -1;
		while (bridge->commands[++i])
			ft_splitfree(bridge->commands[i]);
		free(bridge->commands);
		i = -1;
		while (bridge->redirect && (bridge->redirect[++i].inred
				|| bridge->redirect[i].outred))
		{
			free_redirect(bridge, i);
		}
		if (bridge->redirect)
			free (bridge->redirect);
	}
	free(bridge);
}

static void	free_redirect(t_bdg *bridge, int i)
{
	if (bridge->redirect[i].inred)
	{
		ft_splitfree(bridge->redirect[i].inred->file);
		free(bridge->redirect[i].inred->type);
		free (bridge->redirect[i].inred);
	}
	if (bridge->redirect[i].outred)
	{
		ft_splitfree(bridge->redirect[i].outred->file);
		free(bridge->redirect[i].outred->type);
		free (bridge->redirect[i].outred);
	}
}
