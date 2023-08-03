#include "../../Includes/minishell.h"

static char	*strdupm(char const *s, int start, int end)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc(((end - start) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (start < end)
		dest[i++] = s[start++];
	dest[i] = 0;
	return (dest);
}

static int	count_word(const char *s, char *c)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	while (s[i])
	{
		if (ft_strchr(c, s[i]) && s[i])
		{
			i = i + is_quote((char *)s + i) + 2;
			k++;
		}
		if (s[i])
		{
			k++;
			while (!ft_strchr(c, s[i]) && s[i])
				i++;
		}
	}
	return (k);
}

static char	**ft_split_02(char const *s, char *c, int i, int j)
{
	char	**tabl;
	int		start;
	char	tmp;

	tabl = (char **) malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!tabl)
		return (NULL);
	while (s[i])
	{
		if (is_quote_zero((char *)s + i) != 0)
		{
			tmp = s[i];
			start = ++i;
			i += find_next_char(s + i, tmp);
			if (s[start - 1])
				tabl[j++] = ft_split_utils(s, i, start);
		}
		start = i;
		while (!ft_strchr(c, s[i]) && s[i])
			i++;
		if (start != i)
			tabl[j++] = strdupm(s, start, i);
	}
	tabl[j] = NULL;
	return (tabl);
}

char	*ft_split_utils(const char *s, int i, int start)
{
	char	*res;
	char	*tmp;

	res = strdupm(s, start, i - 1);
	if (start > 1 && ft_is_whitespace(s[start - 2]) == 0)
	{
		tmp = ft_strdup(res);
		free(res);
		res = ft_strjoin_plus("\"", tmp);
		free(tmp);
	}
	if (ft_is_whitespace(s[i]) == 0)
	{
		tmp = ft_strdup(res);
		free(res);
		res = ft_strjoin_plus(tmp, "\"");
		free(tmp);
	}
	return (res);
}

void	fusion_arg(char **line)
{
	char	**res;
	char	*tmp2;
	int		i;

	i = 0;
	res = ft_split_02(*line, "\"\'", 0, 0);
	print_str_tab(res);
	free(*line);
	*line = NULL;
	if (!res)
		return ;
	while (res[i])
	{
		tmp2 = ft_strdup(*line);
		if (*line)
			free(*line);
		*line = ft_strjoin_plus(tmp2, res[i]);
		free(tmp2);
		free(res[i]);
		i++;
	}
	free(res);
}
