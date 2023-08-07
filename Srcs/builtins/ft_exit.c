/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:59:56 by lolefevr          #+#    #+#             */
/*   Updated: 2023/08/06 00:49:00 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void ft_exit(void)
{
	free_trinity();
	safe_free((void **)&g_shell_data->path);
	if (g_shell_data->env)
		free_data(g_shell_data);
	set_termios_mode(TERMIOS_UNMUTE_CTRL);
	exit(EXIT_SUCCESS);
}
