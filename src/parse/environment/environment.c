
#include "../../../minishell.h"

static void	expand_variable(t_parse *parse, char *s);

char	*environments(char *s)
{
	int		i;
	int		j;
	int		quote;
	t_parse	*parse;

	parse = malloc (sizeof (t_parse));
	parse->nb_env = count_env(s);
	if (parse->nb_env == 0)
		return (s);
	parse->env = (char **)malloc (sizeof (char *) * (parse->nb_env + 1));
	i = -1;
	j = -1;
	parse->l_d = 0;
	quote = 0;
	while (s[++i])
	{
		quote = type_of_quote(s, i, quote);
		if (s[i] == '$' && s[i + 1] != ' ' && s[i + 1] != '.' && quote != 1)
			parse->env[++j] = cut_and_get_env(parse, s, i);
	}
	parse->env[++j] = NULL;
	expand_variable(parse, s);
	free(parse->env);
	free(s);
	return (parse->r_env);
}

static	void	expand_variable(t_parse *parse, char *s)
{
	int	quote;
	int	e_len;
	int	i;
	int	e;

	e_len = 0;
	i = -1;
	while (parse->env[++i])
		e_len += ft_strlen(parse->env[i]);
	e_len = e_len - parse->l_d + 1;
	parse->r_env = malloc (sizeof (char *) * (ft_strlen(s) + e_len));
	parse->a = -1;
	i = -1;
	e = -1;
	quote = 0;
	while (s[++i])
	{
		quote = type_of_quote(s, i, quote);
		if (s[i] == '$' && s[i + 1] != ' ' && s[i + 1] != '.'
			&& s[i + 1] && quote != 1)
			i = env_to_str(parse, s, i, ++e);
		else
			parse->r_env[++parse->a] = s[i];
	}
	parse->r_env[++parse->a] = '\0';
}
