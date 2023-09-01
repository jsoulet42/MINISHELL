/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_03.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:22:11 by hnogared          #+#    #+#             */
/*   Updated: 2023/09/01 17:19:56 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	ft_min(int a, int b)
{
	return ((a <= b) * a + (a > b) * b);
}

int	ft_isoperand(char c)
{
	char	to_find[2];

	to_find[0] = c;
	to_find[1] = 0;
	return (c != ':'
		&& ft_strnstr(OPERANDS, to_find, ft_strlen(OPERANDS)));
}

char	**ft_fsplit(char *str, int (*word_len_counter)(char *))
{
	int		word_len;
	char	*word;
	char	**res;

	if (!str || !word_len_counter)
		return (NULL);
	res = NULL;
	while (*str)
	{
		word_len = word_len_counter(str);
		if (word_len < 1)
			return (free_str_tab((void **)res), NULL);
		word = ft_substr(str, 0, word_len);
		if (!word)
			return (free_str_tab((void **)res), NULL);
		str += word_len;
		res = str_tab_add_neo(res, word);
	}
	return (res);
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
