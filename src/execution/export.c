#include "../../minishell.h"

static void	add(char *key);
static int	parse_export(char *str);
static char	*get_key(char *str);

int	b_export(char **commands)
{
	int	i;

	i = 0;
	while (commands[++i])
		add(commands[i]);
	return (0);
}

static void	add(char *str)
{
	char	**new_env;
	char	*key;
	int	i;

	if (parse_export(str))
		return ;
	key = get_key(str);
	if (getenv_value(key))
		b_delete(key);
	new_env = (char **)malloc((env_len(g_env) + 2) * sizeof(char *));
	if (!new_env)
		error_msg("Error memory export");
	i = -1;
	while (g_env[++i])
		new_env[i] = ft_strdup(g_env[i]);
	new_env[i++] = ft_strdup(str);
	new_env[i] = NULL;
	free_env(g_env);
	g_env = new_env;
	free(key);
}

static char	*get_key(char *str)
{
	int	i;
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

static int	parse_export(char *str)
{
	int	i;
	int	equal;

	if (!*str || !ft_isalpha(*str))
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
