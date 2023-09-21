/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_03.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:22:31 by hnogared          #+#    #+#             */
/*   Updated: 2023/09/21 01:06:02 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	next_pipe(char **line_tab)
{
	int	j;

	if (!line_tab)
		return (0);
	j = 0;
	while (line_tab[j] && line_tab[j][0] != '|')
		j++;
	return (j);
}

int	real_cmd(char **line_tab)
{
	int	i;

	if (!line_tab)
		return (0);
	i = 1;
	while (*line_tab)
		i += ((*line_tab++)[0] == '|');
	return (i);
}

char	**new_neo(char *add)
{
	char	**new;

	if (!add)
		return (NULL);
	new = (char **)malloc(sizeof(char *) * 2);
	if (!new)
		return (NULL);
	new[0] = add;
	new[1] = NULL;
	return (new);
}

char	**str_tab_add_neo(char **str, char *add)
{
	int		i;
	char	**new;

	if (!str)
		return (new_neo(add));
	i = str_tab_len(str);
	new = (char **)ft_calloc(sizeof(char *), i + 2);
	if (!new)
		return (NULL);
	i = -1;
	while (str[++i])
		new[i] = str[i];
	free(str);
	new[i] = add;
	new[i + 1] = NULL;
	return (new);
}
