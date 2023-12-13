/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:37:19 by mhernang          #+#    #+#             */
/*   Updated: 2023/11/26 18:37:20 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	parse_export(char *str, int type);
static char	*get_key(char *str);

int	b_export(char **m_env, char **commands)
{
	int	i;

	i = 0;
	while (commands[++i])
		add(m_env, commands[i], NORMAL);
	return (0);
}

void	add(char **m_env, char *str, int type)
{
	char	**new_env;
	char	*key;
	int		i;

	if (parse_export(str, type))
		return ;
	key = get_key(str);
	if (getenv_value(m_env, key))
		b_delete(m_env, key);
	new_env = (char **)malloc((env_len(m_env) + 2) * sizeof(char *));
	if (!new_env)
		exit_msg(ERR_MEMORY, 1);
	i = -1;
	while (m_env[++i])
		new_env[i] = ft_strdup(m_env[i]);
	new_env[i++] = ft_strdup(str);
	new_env[i] = NULL;
	free_env(m_env);
	m_env = new_env;
	free(key);
}

static char	*get_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = (char *)malloc((i + 1) * sizeof(char));
	i = -1;
	while (str[++i] && str[i] != '=')
		key[i] = str[i];
	key[i] = '\0';
	return (key);
}

static int	parse_export(char *str, int type)
{
	int	i;
	int	equal;

	if (!*str || (!ft_isalpha(*str) && type == NORMAL))
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (1);
	}
	i = -1;
	equal = 0;
	while (str[++i] && !equal)
		if (str[i] == '=')
			equal = i;
	if (!equal)
		return (1);
	if (str[equal - 1] == ' ')
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}
