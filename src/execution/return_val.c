#include "../../minishell.h"

void	set_ret_val(int	val)
{
	char	*new_env;
	char	*value;

	value = ft_itoa(val);
	new_env = ft_strjoin("?=", value);
	add(new_env, RETVAL);
	free(value);
	free(new_env);
}

int	get_ret_val()
{
	int	i;

	i = 0;
	while (g_env[i] && g_env[i][0] != '?')
		i++;
	return (ft_atoi(g_env[i] + 2));
}
