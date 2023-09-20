/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:09:31 by jsoulet           #+#    #+#             */
/*   Updated: 2023/09/20 21:15:36 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	free_and_exit(unsigned char num)
{
	free_data(g_shell_data);
	set_termios_mode(TERMIOS_UNMUTE_CTRL);
	close(g_shell_data->in);
	close(g_shell_data->out);
	exit(num);
}

int	ft_exit(int argc, char **argv)
{
	int	nbr;

	if (argc == 1)
	{
		ft_fprintf(STDOUT_FILENO, "mishelle: Exit o7\n");
		free_and_exit(g_shell_data->exit_code);
	}
	if (argc > 2)
	{
		ft_fprintf(STDERR_FILENO, "mishelle: exit: too many arguments\n");
		return (SH_ERROR);
	}
	if (!argv)
		return (SH_ERROR);
	nbr = ft_atoi(argv[1]);
	if (!nbr && *(argv[1]) != '0')
	{
		ft_fprintf(STDERR_FILENO,
			"mishelle: exit: %s: numeric argument required\n", argv[1]);
		free_and_exit(2);
	}
	ft_fprintf(STDOUT_FILENO, "mishelle: Exit o7\n");
	free_and_exit(nbr);
	return (SH_SUCCESS);
}
