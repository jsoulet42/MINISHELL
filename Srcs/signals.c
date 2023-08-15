/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:15:19 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/15 17:23:03 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	main_sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_fprintf(STDERR_FILENO, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (signal == SIGTERM)
		ft_exit();
}

void	parent_sig_handler(int signal)
{
	if (signal == SIGINT)
		ft_fprintf(STDERR_FILENO, "\b^C\n");
	if (signal == SIGQUIT)
		ft_fprintf(STDERR_FILENO, "\b^\\Quit\n");
}
