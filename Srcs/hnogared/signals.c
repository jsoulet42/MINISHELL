/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:45:13 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/21 12:00:00 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
//		ft_fprintf(STDERR_FILENO, "\n");
		rl_replace_line("", 0);
	//	rl_on_new_line();
		rl_redisplay();
	}
	if (signal == SIGTERM)
		free_and_exit();
}
