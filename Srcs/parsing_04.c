/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_04.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:23:23 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/31 14:11:08 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	**create_type_out(char **line_tab)
{
	char	**new;

	if (!line_tab || !*line_tab)
		return (NULL);
	new = NULL;
	while (*line_tab && (*line_tab)[0] != '|')
	{
		if (!ft_strncmp(*line_tab, ">", 2) || !ft_strncmp(*line_tab, ">>", 3))
		{
			new = str_tab_add_neo(new, *line_tab);
			if (!new)
				break ;
		}
		line_tab++;
	}
	return (new);
}

char	**create_type_in(char **line_tab)
{
	char	**new;

	if (!line_tab || !*line_tab)
		return (NULL);
	new = NULL;
	while (*line_tab && (*line_tab)[0] != '|')
	{
		if (!ft_strncmp(*line_tab, "<", 2) || !ft_strncmp(*line_tab, "<<", 3))
		{
			new = str_tab_add_neo(new, *line_tab);
			if (!new)
				break ;
		}
		line_tab++;
	}
	return (new);
}

char	**create_file_out(char **line_tab)
{
	char	**new;

	if (!line_tab || !*line_tab)
		return (NULL);
	new = NULL;
	while (*line_tab && (*line_tab + 1)[0] != '|')
	{
		if (!ft_strncmp(*line_tab, ">", 2) || !ft_strncmp(*line_tab, ">>", 3))
		{
			new = str_tab_add_neo(new, *(line_tab++ + 1));
			if (!new)
				break ;
		}
		line_tab++;
	}
	return (new);
}

char	**create_file_in(char **line_tab)
{
	char	**new;

	if (!line_tab || !*line_tab)
		return (NULL);
	new = NULL;
	while (*line_tab && (*line_tab + 1)[0] != '|')
	{
		if (!ft_strncmp(*line_tab, "<", 2) || !ft_strncmp(*line_tab, "<<", 3))
		{
			new = str_tab_add_neo(new, *(line_tab++ + 1));
			if (!new)
				break ;
		}
		line_tab++;
	}
	return (new);
}

char	**create_kafka(char **line_tab)
{
	char	**new;

	if (!line_tab || !*line_tab)
		return (NULL);
	new = NULL;
	while (*line_tab && (*line_tab + 1)[0] != '|')
	{
		if (!ft_strncmp(*line_tab, "<", 2) || !ft_strncmp(*line_tab, "<<", 3)
			|| !ft_strncmp(*line_tab, ">", 2)
			|| !ft_strncmp(*line_tab, ">>", 3))
		{
			new = str_tab_add_neo(new, *line_tab);
			if (!new)
				break ;
		}
		line_tab++;
	}
	return (new);
}
