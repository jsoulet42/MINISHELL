/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:09:31 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/15 17:22:02 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	ft_exit(void)
{
	free_data(g_shell_data);
	set_termios_mode(TERMIOS_UNMUTE_CTRL);
	ft_printf("mishelle: Exit o7\n");
	exit(EXIT_SUCCESS);
}
