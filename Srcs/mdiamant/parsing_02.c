/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:30:43 by mdiamant          #+#    #+#             */
/*   Updated: 2023/07/27 16:28:35 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int		find_next_char(char *str, char *c);

/*char *cas_specifique_01(char *line, int i)
{
	char	*res;
	char	*tmp;
	int		j;
	char	c;

	c = line[i];
	tmp = ft_substr(line, 0, i - 1);


	free(line);
	return (res);

}*/
char *prev_line(char *line, int i)
{
	char	*res;
	char	*tmp;
	int		j;


	i = i + find_next_char(line + i, "\"\'") + 1;
	if(i > 0 && line[i - 1] != ' ' && line[i - 1] != '\t' && line[i - 1] != '\v')
	{
			return (prev_line(line, i));
	}
	i = i + find_next_char(line + i, "\"\'") + 1;
	if (!line[i])
		return (line);
	if (line[i] != ' ' && line[i] != '\t' && line[i] != '\v')
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			res = ft_substr(line, 0, ++i - 2);
			tmp = ft_substr(line, i , ft_strlen(line) - i);
			free(line);
			line = ft_strjoin(res, tmp);
			free(res);
			free(tmp);
			i += find_next_char(line + i, "\"\'");
			if (line[i] == '\'')
				line[i] = '\"';
		}
		else
		{
			j = i;
			while (line[j] && line[j] != ' ' && line[j] != '\t' && line[j] != '\v' && line[j] != '\"' && line[j] != '\'')
				j++;
			tmp = malloc(sizeof(char) * (j - i + 2));
			j = i;
			while (line [j] && line[j] != ' ' && line[j] != '\t' && line[j] != '\v')
			{
				tmp[j - i] = line[j];
				j++;
			}
			tmp[j - i] = '\"';
			tmp[(j - i) + 1] = '\0';
			ft_fprintf(2, "tmp : [%s]\n", tmp);
			j = 0;
			i--;
			while(tmp[j])
			{
				line[i] = tmp[j];
				i++;
				j++;
			}
			free(tmp);
		}
	}
	line = prev_line(line, i);
	return (line);
}

int	find_next_char(char *str, char *c)
{
	int	i;
	int j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (c[j])
		{
			if (str[i] == c[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}
