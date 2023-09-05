/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:19:21 by hnogared          #+#    #+#             */
/*   Updated: 2023/09/04 17:23:50 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	check_line_words(const char **line_tab)
{
	int		test;
	int		test2;
	char	**temp;

	if (!line_tab || !*line_tab)
		return (SH_ERROR);
	temp = (char **)line_tab - 1;
	while (*(++temp))
	{
		test = ft_isoperand(**temp);
		if (*(temp + 1))
			test2 = ft_isoperand(*(temp + 1)[0]);
		if (test && (!*(temp + 1) || test2))
		{
			printf("mishelle: syntax error bad operand `");
			printf("%s'\n", *temp);
			return (SH_ERROR);
		}
	}
	return (SH_SUCCESS);
}

static int	pw(int i, char c)
{
	int	j;

	j = 0;
	if (i < 0)
	{
		j += ft_fprintf(2, "\t|\n");
		return (j);
	}
	while (i--)
		j += ft_fprintf(2, "%c", c);
	j += ft_fprintf(2, "|\n");
	return (j);
}

static int	print_strstr(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str || !str[0])
		return (ft_fprintf(2, "NULL"));
	while (str[i])
	{
		j += ft_fprintf(2, "[%s] ", str[i]);
		i++;
	}
	return (j);
}

static void	print_t_rinity_02(t_rinity **t, int i, int j, int len)
{
	j = ft_fprintf(2, "|\ttype_out : ");
	j += print_strstr(t[i]->type_out);
	pw(len - j, ' ');
	j = ft_fprintf(2, "|\tfile_in  : ");
	j += print_strstr(t[i]->file_in);
	pw(len - j, ' ');
	j = ft_fprintf(2, "|\tfile_out : ");
	j += print_strstr(t[i]->file_out);
	pw(len - j, ' ');
	j = ft_fprintf(2, "|\tkafka    : ");
	j += print_strstr(t[i]->kafka);
	pw(len - j, ' ');
	ft_fprintf(2, "|______________________________");
	ft_fprintf(2, "_______________________|\n\n");
}

void	print_t_rinity(t_rinity **t)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	if (!t)
		return ;
	while (t[i])
	{
		len = ft_fprintf(2, " _________________________");
		len += ft_fprintf(2, "____________________________") - 6;
		ft_fprintf(2, "\n|");
		pw(len + 5, ' ');
		j = ft_fprintf(2, "|\tLa commande est : ");
		j += print_strstr(t[i]->cmd);
		pw(len - j, ' ');
		j = ft_fprintf(2, "|\ttype_in  : ");
		j += print_strstr(t[i]->type_in);
		pw(len - j, ' ');
		print_t_rinity_02(t, i, j, len);
		i++;
	}
}
