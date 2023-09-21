/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:00:14 by hnogared          #+#    #+#             */
/*   Updated: 2023/09/21 07:58:44 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

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

char	*join_str_tab_mono(const char **str_tab)
{
	char	*temp;
	char	**temp_tab;

	if (!str_tab)
		return (NULL);
	temp_tab = (char **)str_tab;
	while (*(temp_tab + 1))
	{
		temp = ft_strjoin(*temp_tab, " ");
		if (!temp)
			return (NULL);
		free(*temp_tab);
		*temp_tab++ = temp;
	}
	return (join_str_tab(str_tab));
}

void	ft_supprchar(char **str, int i)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_substr(*str, 0, i);
	tmp2 = ft_substr(*str, i + 1, ft_strlen(*str));
	free(*str);
	*str = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
}
