/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:30:43 by mdiamant          #+#    #+#             */
/*   Updated: 2023/07/28 19:14:16 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"


void	add_char(char **str, int i, char *c);
void	supp_char(char **str, int i);
void	fusion_nocotcot(char **line, int i);

static char	*strdupm(char const *s, int start, int end)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc(((end - start) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (start < end)
	{
		dest[i++] = s[start++];
	}
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
			i += 1; //find_next_char((char *)s + i, (char)s[i]);
		if (s[i])
		{
			k++;
			while (!ft_strchr(c, s[i]) && s[i])
				i ++;
		}
	}
	return (k);
}

char	**ft_split_02(char const *s, char *c)
{
	char	**tabl;
	int		start;
	int		i;
	int		j;

	tabl = (char **) malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!tabl)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (ft_strchr(c, s[i]) && s[i])
				i += 1; // find_next_char((char *)s + i, s[i]);
		start = i;
		while (!ft_strchr(c, s[i]) && s[i])
				i++;
		if (start != i)
			tabl[j++] = strdupm(s, start, i);
	}
	tabl[j] = 0;
	return (tabl);
}

void	fusion_arg_02(char **line)
{
	char	**res;
	char	*tmp2;
	int		i;

	i = 0;
	res = ft_split_02(*line, "\"\'");
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
/*
void	fusion_arg(char **line, int i)
{
	char	*c;


	if (g_debug_fusion++ > 10)
	{
		ft_fprintf(2, "bug\n");
		return ;
	}

	if (!line || !*line || !(*line)[i])
		return ;
	i += find_next_char(*line + i, "\"\'");
	ft_fprintf(2, "celui d'avant : [[[%c]]]\n", (*line)[i - 1]);

	if ((*line)[i] && i > 0 && !ft_iswhitespace(*line, i - 1) && (*line)[i - 1] != '\"' && (*line)[i - 1] != '\'')
	{
		ft_fprintf(2, "fusion_nocotcot\n");
		fusion_nocotcot(line, i);
		return ;
	}
	c = ft_substr(*line, i++, 1);
	i += find_next_char(*line + i, c) + 1;
	if((*line)[i] && (*line)[i] == (*line)[i - 1])
	{
		ft_fprintf(2, "double suppr\n");
		supp_char(line, --i);
		supp_char(line, i);
		i += find_next_char(*line + i, c);
		if (!ft_iswhitespace(*line, i))
			i += 1;
		free(c);
		ft_fprintf(2, "line + i : [%s]\n", i - 1);
		fusion_arg(line, i - 1);
		return ;
	}
}

int is_quote_good(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			if (i > 0 && !ft_iswhitespace(line, i - 1))
				return (i);
		}
		i++;
	}
}

void fusion_nocotcot(char **line, int i)
{
	char	*c;

	ft_fprintf(2, "line + i : [%s]\n", *line + i);
	c = ft_substr(*line, i, 1);
	supp_char(line, i);
	ft_fprintf(2, "supp_char : [%s]\n", *line);
	i--;
	while ((!ft_iswhitespace(*line, i)))
		i--;
	add_char(line, ++i, c);
	ft_fprintf(2, "add_char : [%s]\n", *line);
	i += find_next_char(*line + i, c) + 1;
	i += find_next_char(*line + i, c) + 1;
	ft_fprintf(2, "line + i : [%s]\n", *line + i);
	fusion_arg(line, i);
	free(c);
}
int	ft_iswhitespace(char *str, int i)
{
	if (!str || i < 0 || !str[i])
		return (0);
	if ((str[i] < 9 && str[i] > 13) || str[i] == 32 || str[i] == 127)
		return (1);
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

char *cas_specifique_01(char *line, int i)
{
	char	*res;
	char	*tmp;
	int		j;
	char	c;

	c = line[i];
	tmp = ft_substr(line, 0, i - 1);


	free(line);
	return (res);

}
char *fusion_arg(char *line, int i)
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
*/
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
