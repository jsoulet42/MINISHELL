/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:27:25 by lolefevr          #+#    #+#             */
/*   Updated: 2023/07/18 13:37:42 by lolefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	signal_c(int signal)
{
	if (signal)
	{
		// tout free et faire une nouvelle ligne
	}
}

void	signal_d(int signal)
{
	if (signal)
	{
			// tout free est exit
	}
}

void	init_signal(void)
{
	signal(SIGINT, signal_c);
	signal(SIGTERM, signal_d);
	signal(SIGQUIT, signal_d);
	signal(SIGTSTP, signal_d);
}
