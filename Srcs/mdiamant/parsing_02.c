/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:30:43 by mdiamant          #+#    #+#             */
/*   Updated: 2023/07/31 12:19:15 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			i = i + find_next_char(s + i, tmp);
			tabl[j++] = strdupm(s, start, i - 1);
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

int	find_next_char(const char *str, const char c)
{
	int	i;

	if (!*str)
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] == c)
			return (i + 1);
		i++;
	}
	return (i);
}
