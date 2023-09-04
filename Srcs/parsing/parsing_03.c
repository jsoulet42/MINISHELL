/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_06.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:24:30 by jsoulet           #+#    #+#             */
/*   Updated: 2023/09/04 13:02:38 by hnogared         ###   ########.fr       */
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

int	str_tab_len(char **str)
{
	int	i;

	i = 0;
	if (!*str)
		return (0);
	while (str[i])
		i++;
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
