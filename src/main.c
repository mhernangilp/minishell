/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:02:26 by gfernand          #+#    #+#             */
/*   Updated: 2023/09/26 14:08:34 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv)
{
	char	*input;

	atexit(leaks);
	(void) argv;
	if (argc != 1)
	{
		printf("Wrong parameters\n");
		exit(1);
	}
	while (1)
	{
		input = readline(ENTRADA_MS);
		if (input == NULL)
		{
			printf("exit\n");
			exit(1);
		}
		add_history(input);
		check_pipes(input);
	/*	CREAR HISTORIAL
		PARSEO
		EJECUCIÓN
			(builtins(input))*/
		free(input);
	}
	return (0);
}
void	builtins(char *input)
{
	char	*buffer;

	buffer = malloc (sizeof (size_t));
	if (ft_strcmp(input, "exit") > 0)
	{
		printf("exit\n");
		exit(1);
	}
	else if (ft_strcmp(input, "pwd") > 0)
	{
		if (getcwd(buffer, 1024) != NULL)
		{
			printf("%s\n", buffer);
			free(buffer);
		}
	}
	free(buffer);
}

int	ft_strcmp(char *str, char *cmp)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != cmp[i])
			return (-1);
	}
	if (cmp[i])
		return (-1);
	return (i);
}
