/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 02:14:43 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/20 17:32:01 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	safe_free(void **ptr_addr)
{
	if (!ptr_addr || !*ptr_addr)
		return ;
	free(*ptr_addr);
	*ptr_addr = NULL;
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
	safe_free((void **) &shell_data);
	rl_clear_history();
}

void	free_and_exit(void)
{
	int	exit_code;

	exit_code = 0;
	/* TODO implement exit code inside g_shell_data */
//	exit_code = g_shell_data->exit_code;
	free_data(g_shell_data);
	exit(exit_code);
}
