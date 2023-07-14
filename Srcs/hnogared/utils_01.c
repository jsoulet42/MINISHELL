/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:47:41 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/14 18:45:15 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	safe_free(void **ptr_addr)
{
	if (*ptr_addr)
	{
		free(*ptr_addr);
		*ptr_addr = NULL;
	}
}

void	print_str_tab(char **str_tab)
{
	if (!str_tab)
		return ;
	while (*str_tab)
		printf("%s\n", *str_tab++);
}

void	free_str_tab(char **str_tab)
{
	int	i;

	if (!str_tab)
		return ;
	i = 0;
	while (str_tab[i])
		free(str_tab[i++]);
	free(str_tab);
	str_tab = NULL;
}
