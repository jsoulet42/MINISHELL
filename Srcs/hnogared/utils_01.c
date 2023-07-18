/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:47:41 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/18 14:38:42 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

char	**order_str_tab(char **str_tab, char limit)
{
	int		len;
	int		id[2];
	char	*temp;

	if (!str_tab || !str_tab[0] || !str_tab[1])
		return (str_tab);
	id[0] = 0;
	id[1] = 1;
	while (str_tab[id[0] + 1])
	{
		len = SH_MIN(ft_strchr(str_tab[id[0]], limit) - str_tab[id[0]],
				ft_strchr(str_tab[id[1]], limit) - str_tab[id[1]]) + 1;
		if (ft_strncmp(str_tab[id[0]], str_tab[id[1]], len) > 0)
		{
			temp = str_tab[id[0]];
			str_tab[id[0]] = str_tab[id[1]];
			str_tab[id[1]] = temp;
		}
		id[1]++;
		if (str_tab[id[1]])
			continue ;
		id[0]++;
		id[1] = id[0] + 1;
	}
	return (str_tab);
}

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

void	free_data(t_shell *shell_data)
{
	if (shell_data->env)
		free_env(&shell_data->env);
	if (shell_data->par)
		free_t_par(shell_data->par);
	rl_clear_history();
}
