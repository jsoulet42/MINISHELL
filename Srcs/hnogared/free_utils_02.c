/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:14:24 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/07 15:03:42 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	free_and_return(void)
{
	free_trinity();
	if (g_shell_data)
		free_data(g_shell_data);
	set_termios_mode(TERMIOS_UNMUTE_CTRL);
}
