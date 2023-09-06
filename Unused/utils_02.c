/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:00:14 by hnogared          #+#    #+#             */
/*   Updated: 2023/09/06 14:24:55 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

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
