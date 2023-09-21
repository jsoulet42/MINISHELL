/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:14:17 by jsoulet           #+#    #+#             */
/*   Updated: 2023/09/21 15:35:05 by hnogared         ###   ########.fr       */
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

void	free_data(t_shell shell_data)
{
	rl_clear_history();
	if (shell_data.t)
		free_trinity_tab(&shell_data.t);
	if (shell_data.env)
		free_env(&shell_data.env);
}

void	free_trinity_struct(t_rinity *t)
{
	if (!t)
		return ;
	safe_free((void **)&t->cmd_path);
	free_str_tab((void **)t->cmd);
	free_str_tab((void **)t->file_in);
	free_str_tab((void **)t->file_out);
	free_str_tab((void **)t->type_in);
	free_str_tab((void **)t->type_out);
	free(t);
}

void	free_trinity_tab(t_rinity ***t)
{
	int	i;

	if (!t || !*t || !**t)
		return ;
	i = 0;
	while ((*t)[i])
		free_trinity_struct((*t)[i++]);
	free(*t);
	*t = NULL;
}
