
#include "../minishell.h"

static int	count_env(char *s);
static char	*cut_and_get_env(t_parse *parse, char *s, int i);
static void	expand_variable(t_parse *parse, char *s);
static int	env_to_str(t_parse *parse, char *s, int i, int e);
static int	type_of_quote(char *str, int i, int quote);

char	*environments(t_parse *parse, char *str)
{
	int	i;
	int	j;
	int	quote;

	parse->nb_env = count_env(str);
	if (parse->nb_env == 0)
		return (str);
	parse->env = (char **)malloc (sizeof (char *) * (parse->nb_env + 1));
	i = -1;
	j = -1;
	parse->l_d = 0;
	quote = 0;
	while (str[++i])
	{
		quote = type_of_quote(str, i, quote);
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '.' && quote != 1)
			parse->env[++j] = cut_and_get_env(parse, str, i);
	}
	parse->env[++j] = NULL;
	expand_variable(parse, str);
	free(parse->env);
	free(str);
	return (parse->r_env);
}

static int	count_env(char *s)
{
	int	i;
	int	count_env;
	int	doble_quote;

	i = -1;
	count_env = 0;
	doble_quote = 0;
	while (s[++i])
	{
		if (s[i] == '"' && doble_quote)
			doble_quote = 0;
		else if (s[i] == '"' && !doble_quote)
			doble_quote = 2;
		else if (s[i] == '\'' && !doble_quote)
			i = quote(s, i);
		else if (s[i] == '$' && s[i + 1] != ' ' && s[i + 1] != '.' && s[i + 1])
			count_env++;
	}
	return (count_env);
}

static int	type_of_quote(char *str, int i, int quote)
{
	if (str[i] == '\'' && !quote)
		quote = 1;
	else if (str[i] == '"' && !quote)
		quote = 2;
	else if ((str[i] == '\'' && quote == 1) || (str[i] == '"' && quote == 2))
		quote = 0;
	return (quote);
}

static char	*cut_and_get_env(t_parse *parse, char *s, int i)
{
	char	*env;
	char	*aux;
	int		start;

	start = ++i;
	while (s[i] && s[i] != '\'' && s[i] != '"' && s[i] != ' ' && s[i] != '\t' && s[i] != '$')
		i++;
	parse->l_d += i - start + 1;
	aux = ft_substr(s, start, i - start);
	env = getenv(aux);
	free (aux);
	return (env);
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
		if (s[i] == '$' && s[i + 1] != ' ' && s[i + 1] != '.' && s[i + 1] && quote != 1)
			i = env_to_str(parse, s, i, ++e);
		else
			parse->r_env[++parse->a] = s[i];
	}
	parse->r_env[++parse->a] = '\0';
}

static	int	env_to_str(t_parse *parse, char *s, int i, int e)
{
	int	j;

	if (parse->env[e])
	{
		j = -1;
		while (parse->env[e][++j])
			parse->r_env[++parse->a] = parse->env[e][j];
	}
	i++;
	while (s[i] && s[i] != '\'' && s[i] != '"' && s[i] != ' ' && s[i] != '\t' && s[i] != '$')
		i++;
	return (i - 1);
}
