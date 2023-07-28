/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:30:43 by mdiamant          #+#    #+#             */
/*   Updated: 2023/07/28 12:39:37 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"


void	add_char(char **str, int i, char *c);
void	supp_char(char **str, int i);

int g_debug_fusion_arg = 0;

void	fusion_arg(char **line, int i)
{
	if (g_debug_fusion_arg++ > 10)
	{
		ft_fprintf(2, "ERROR : g_debug_fusion_arg > 10\n");
		return ;
	}
	char	*c;

	c = NULL;
	if (!line || !*line || !(*line)[i])
	{
		ft_fprintf(2, "sortie de la recursivité\n");
		return ;
	}
	i += find_next_char(*line + i, "\"\'");
	if ((*line)[i] && i > 0 && ft_iswhitespace(*line, i - 1) == 0)
	{
		c = ft_substr(*line, i, 1);
		supp_char(line, i);
		ft_fprintf(2, "supp_char : [%s]\n", *line);
		i--;
		while ((ft_iswhitespace(*line, i) == 0))
			i--;
		add_char(line, ++i, c);
		ft_fprintf(2, "add_char : [%s]\n", *line);
		i += find_next_char(*line + i, c) + 1;
		i += find_next_char(*line + i, c) + 1;
		ft_fprintf(2, "line + i : [%s]\n", *line + i);
		fusion_arg(line, i);
		free(c);
	}
	else
	{
		i++;
		i += find_next_char(*line + i, "\"\'");
		if((*line)[i] && ft_iswhitespace(*line, i) == 0)
		{
			c = ft_substr(*line, i, 1);
			supp_char(line, i);
			while ((ft_iswhitespace(*line, i) == 0))
				i++;
			add_char(line, ++i, c);
			fusion_arg(line, i);
			free(c);
		}
	}
}
int	ft_iswhitespace(char *str, int i)
{
	if (i == 0)
		return (0);
	if ((str[i] < 9 && str[i] > 13) || str[i] == 32 || str[i] == 127)
		return (i);
	return (0);
}
int	ft_isdol(char *str, int beg, int end)
{
	int	i;

	i = beg;
	if (end < 0)
		end = ft_strlen(str);
	while (str[i] && i < end)
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (0);
}
void	supp_char(char **str, int i)
{
	char	*tmp1;
	char	*tmp2;

	if(!str || !*str)
		return ;
	tmp1 = ft_substr(*str, 0, i);
	tmp2 = ft_substr(*str, i + 1, ft_strlen(*str) - i);
	free(*str);
	*str = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
}
void	add_char(char **str, int i, char *c)
{
	char	*tmp1;
	char	*tmp2;

	if(!str || !*str)
		return ;
	tmp1 = ft_substr(*str, 0, i);
	tmp2 = ft_strjoin(tmp1, c);
	free(tmp1);
	tmp1 = ft_substr(*str, i, ft_strlen(*str) - i);
	free(*str);
	*str = ft_strjoin(tmp2, tmp1);
	free(tmp1);
	free(tmp2);
}

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
/*char *fusion_arg(char *line, int i)
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
}*/

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
