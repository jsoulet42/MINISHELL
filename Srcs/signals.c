/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:15:19 by jsoulet           #+#    #+#             */
/*   Updated: 2023/09/21 01:00:04 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	main_sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_fprintf(STDOUT_FILENO, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_shell_data.exit_code = 130;
	}
}

void	heredoc_sig_handler(int signal)
{
	if (signal == SIGINT)
		ft_fprintf(STDOUT_FILENO, "^C");
	ft_fprintf(STDOUT_FILENO, "\n");
}

void	parent_sig_handler(int signal)
{
	if (signal == SIGQUIT)
		ft_fprintf(STDOUT_FILENO, "mishelle: quit");
	ft_fprintf(STDOUT_FILENO, "\n");
}
