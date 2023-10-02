
#include "../../minishell.h"

static char	**ft_word(char **str, const char *s, char c, int count);
static char	**ft_free(char **str);
static	int	ft_count(const char *s, char c);

char	**split_quote(const char *s, char c)
{
	int		i;
	int		count;
	char	**str;

	i = 0;
	count = ft_count(s, c);
/*	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1])
			count++;
		i++;
	}
	if (s[0] == c || s[0] == '\0')
		count--;*/
	str = (char **)malloc(sizeof(char *) *(count + 1));
	if (!str)
		return (NULL);
	ft_word(str, s, c, count);
	return (str);
}

static char	**ft_word(char **str, const char *s, char c, int count)
{
	int	i;
	int	found;
	int	start;
	int quote;

	i = 0;
	found = 1;
	quote = 0;
	while (found <= count)
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && !quote)
			{
				if (s[i] == '"' || s[i] == '\'')
				{
					quote = 1;
					while (s[i] && quote)
					{
						if (s[i] == '"' || s[i] == '\'')
							quote = -1;
						i++;
					}
				}
				else if (s[i] == c)
					quote = 3;
				i++;
			}
			str[found - 1] = ft_substr(s, start, (i - start));
			if (str == NULL)
				return (ft_free(str));
			found++;
		}
		else
			i++;
	}
	str[found - 1] = NULL;
	return (str);
}

static char	**ft_free(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static	int	ft_count(const char *s, char c)
{
	int	i;
	int	count;
	int	quote;

	quote = 0;
	count = 1;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			quote = 1;
			while (s[i] && quote)
			{
				if (s[i] == '"' || s[i] == '\'')
					quote = -1;
				i++;
			}
		}
		else if (s[i] == c && s[i + 1] != c && s[i + 1])
				count++;
	}
	if (s[0] == c || s[0] == '\0')
		count--;
	if (quote == 1)
		return (-1);
	printf("count %d\n", count);
	return (count);
}
