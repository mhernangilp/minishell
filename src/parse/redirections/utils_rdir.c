
#include "../../../minishell.h"

void	count_redirections(t_parse *parse, char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '<')
		{
			i++;
			parse->n_ip++;
		}
		if (s[i] == '>')
		{
			i++;
			parse->n_op++;
		}
	}
}

int	malloc_redirect(t_parse *parse, char **s, int i, int j)
{

	if (s[i][j + 1] == '<' || s[i][j + 1] == '>')
		j += 2;
	else
		j++;
	while (s[i][j] == ' ' || s[i][j] == '\t')
		j++;
	while (s[i][j] && s[i][j] != ' ' && s[i][j] != '\t' && s[i][j] != '<'
				&& s[i][j] != '>')
		j++;
	parse->rdirect = ft_substr(s[i], parse->start_rdir, j - parse->start_rdir);
	printf("%d REDIRECT->%s\n", i, parse->rdirect);
	return (j);
}

char	**out_redirect(t_parse *parse, char **s, int i, int j)
{
	int	m;

	m = parse->start_rdir;
	while (s[i][m] && m <= j)
	{
		s[i][m] = ' ';
		m++;
	}
	return (s);
}
