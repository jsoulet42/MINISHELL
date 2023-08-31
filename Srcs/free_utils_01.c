/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:14:17 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/30 22:44:28 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	safe_free(void **ptr_addr)
{
	if (!ptr_addr || !*ptr_addr)
		return ;
	free(*ptr_addr);
	*ptr_addr = NULL;
}

void	free_str_tab(void **str_tab)
{
	int	i;

	if (!str_tab)
		return ;
	if (!*str_tab)
	{
		free(str_tab);
		str_tab = NULL;
		return ;
	}
	i = 0;
	while (str_tab[i])
	{
		free(str_tab[i]);
		str_tab[i++] = NULL;
	}
	free(str_tab);
	str_tab = NULL;
}

void	free_data(t_shell *shell_data)
{
	free_trinity(g_shell_data->t);
	if (shell_data->env)
		free_env(&shell_data->env);
	safe_free((void **) &shell_data);
	rl_clear_history();
}

void	free_trinity(t_rinity **t)
{
	int	i;

	i = 0;
	if (t && t[0])
	{
		while (t[i])
		{
			safe_free((void **)&t[i]->cmd);
			safe_free((void **)&t[i]->kafka);
			safe_free((void **)&t[i]->file_in);
			safe_free((void **)&t[i]->file_out);
			safe_free((void **)&t[i]->type_in);
			safe_free((void **)&t[i]->type_out);
			safe_free((void **)&t[i++]);
		}
		free(t);
		safe_free((void **)&g_shell_data->path);
	}
	return ;
}
