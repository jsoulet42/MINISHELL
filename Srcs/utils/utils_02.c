/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 23:36:22 by hnogared          #+#    #+#             */
/*   Updated: 2023/09/06 14:26:08 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	lentab(char **tableau)
{
	int	i;

	i = -1;
	while (tableau[++i])
		i = i;
	return (i);
}

char	*ft_strchrnul(const char *str, int c)
{
	char	*temp;

	if (!str)
		return (NULL);
	temp = ft_strchr(str, c);
	if (!temp)
		return (ft_strchr(str, 0));
	return (temp);
}

char	*join_str_tab(const char **str_tab)
{
	char	*res;
	char	*temp;
	char	**temp_tab;

	if (!str_tab || !*str_tab)
		return (NULL);
	if (!*(str_tab + 1))
		return (ft_strdup(*str_tab));
	res = NULL;
	temp_tab = (char **)str_tab;
	while (*temp_tab)
	{
		temp = ft_strjoin_plus(res, *temp_tab);
		safe_free((void **)&res);
		if (!temp)
			return (NULL);
		res = temp;
		temp_tab++;
	}
	return (res);
}

static int	get_words_count(const char *str, char sep)
{
	int		count;
	char	*temp;

	if (!str)
		return (0);
	temp = (char *)str + 1;
	count = 1;
	while (*temp)
	{
		if (*temp == sep)
			count++;
		temp++;
	}
	return (count);
}

char	**ft_keep_split(char *str, char sep)
{
	int		count;
	char	**res;
	char	**temp;

	if (!str)
		return (NULL);
	count = get_words_count((const char *)str, sep);
	res = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!res)
		return (NULL);
	res[0] = NULL;
	temp = res;
	count = 0;
	str -= 1;
	while (*(++str))
	{
		if (res[0] && *str != sep)
			continue ;
		count = (uintptr_t)ft_strchrnul(str + 1, sep) - (uintptr_t)str;
		*temp++ = ft_substr(str, 0, count);
		if (!*(temp - 1))
			return (free_str_tab((void **)res), NULL);
		str += count - 1;
	}
	return (res);
}
