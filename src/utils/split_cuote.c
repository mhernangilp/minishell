
#include "../../minishell.h"

static char	**ft_word(char **str, const char *s, char c, int count);

char	**split_quote(const char *s, char c)
{
	int		i;
	int		count;
	char	**str;

	i = 0;
	count = 1;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1])
			count++;
		i++;
	}
	if (s[0] == c || s[0] == '\0')
		count--;
	str = (char **)malloc(sizeof(char *) *(count + 1));
	if (!str)
		return (NULL);
	ft_site(str, s, c, count);
	return (str);
}

static char	**ft_word(char **str, const char *s, char c, int count)
{
	int	i;
	int	found;
	int	start;

	i = 0;
	found = 1;
	while (found <= count)
	{
		if (s[i] != c)
		{
			start = i++;
			while (s[i] != c && s[i])
				i++;
			str[found - 1] = ft_substr(s, start, (i - start);
			if (str == NULL)
				return (ft_splitfree(str));
			found++;
		}
		else
			i++;
	}
	str[found - 1] = NULL;
	return (str);
}

char	**ft_splitfree(char **str)
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
