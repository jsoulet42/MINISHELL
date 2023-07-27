/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 02:14:43 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/27 18:03:27 by jsoulet          ###   ########.fr       */
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

void	free_str_tab(void **str_tab)
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
	/*if (shell_data->par)
	{
		free_t_par(shell_data->par);
		shell_data->par = NULL;
	}*/
	safe_free((void **) &shell_data);
	rl_clear_history();
}

void	free_and_exit(void)
{
	int	exit_code;

	exit_code = 0;
	ft_fprintf(2,"entrée dans free_and_exit\n");
	/* TODO implement exit code inside g_shell_data */
//	exit_code = g_shell_data->exit_code;
	if (g_shell_data && g_shell_data->t && g_shell_data->t[0]
		&& g_shell_data->t[0]->kafka)
	{
		safe_free((void **)&g_shell_data->t[0]->kafka);
		safe_free((void **)&g_shell_data->t[0]->kafka[0]);
		free_str_tab((void **)g_shell_data->t);
		safe_free((void **)&g_shell_data->path);
	}
	if (g_shell_data)
		free_data(g_shell_data);
	set_termios_mode(TERMIOS_UNMUTE_CTRL);
	exit(exit_code);
}
