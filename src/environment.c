
#include "../minishell.h"

static int	count_env(char *s);
static char	*cut_and_get_env(t_parse *parse, char *s, int i);
static void	expand_variable(t_parse *parse, char *s);
static int	env_to_str(t_parse *parse, char *s, int i, int e);

char	*environments(t_parse *parse, char *str)
{
	int		i;
	int		j;

	parse->nb_env = count_env(str);
	if (parse->nb_env == 0)
		return (str);
	parse->env = (char **)malloc (sizeof (char *) * (parse->nb_env + 1));
	i = -1;
	j = -1;
	parse->l_d = 0; 
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '.')
		{
			parse->env[++j] = cut_and_get_env(parse, str, i);
			//printf("ENV%d %s\n", j, parse->env[j]);
		}
	}
	parse->env[++j] = NULL;
//	ft_splitfree(parse->env);
	expand_variable(parse, str);
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
	while (s[++i])
	{
		if (s[i] == '$' && s[i + 1] != ' ' && s[i + 1] != '.' && s[i + 1])
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
