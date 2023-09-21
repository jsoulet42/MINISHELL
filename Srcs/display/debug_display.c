/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:19:21 by hnogared          #+#    #+#             */
/*   Updated: 2023/09/21 06:35:13 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static int	pw(int i, char c)
{
	int	j;

	j = 0;
	if (i < 0)
		return (ft_fprintf(STDERR_FILENO, "\t|\n"));
	while (i--)
		j += ft_fprintf(STDERR_FILENO, "%c", c);
	j += ft_fprintf(STDERR_FILENO, "|\n");
	return (j);
}

static void	print_t_rinity_02(t_rinity **t, int i, int j, int len)
{
	j = ft_fprintf(STDERR_FILENO, "|\ttype_out : ");
	j += print_str_tab(STDERR_FILENO, t[i]->type_out);
	pw(len - j, ' ');
	j = ft_fprintf(STDERR_FILENO, "|\tfile_in  : ");
	j += print_str_tab(STDERR_FILENO, t[i]->file_in);
	pw(len - j, ' ');
	j = ft_fprintf(STDERR_FILENO, "|\tfile_out : ");
	j += print_str_tab(STDERR_FILENO, t[i]->file_out);
	pw(len - j, ' ');
	ft_fprintf(STDERR_FILENO, "|______________________________");
	ft_fprintf(STDERR_FILENO, "_______________________|\n\n");
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
		len = ft_fprintf(STDERR_FILENO, " _________________________");
		len += ft_fprintf(STDERR_FILENO, "____________________________") - 6;
		ft_fprintf(STDERR_FILENO, "\n|");
		pw(len + 5, ' ');
		j = ft_fprintf(STDERR_FILENO, "|\tLa commande est : ");
		j += print_str_tab(STDERR_FILENO, t[i]->cmd);
		pw(len - j, ' ');
		j = ft_fprintf(STDERR_FILENO, "|\ttype_in  : ");
		j += print_str_tab(STDERR_FILENO, t[i]->type_in);
		pw(len - j, ' ');
		print_t_rinity_02(t, i, j, len);
		i++;
	}
}
