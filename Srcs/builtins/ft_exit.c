/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:09:31 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/31 20:15:53 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	free_and_exit(unsigned char num)
{
	free_data(g_shell_data);
	set_termios_mode(TERMIOS_UNMUTE_CTRL);
	exit(num);
}

int	ft_exit(int argc, char **argv)
{
	int	nbr;

	if (argc == 0)
	{
		ft_fprintf(STDOUT_FILENO, "mishelle: Exit o7\n");
		free_and_exit(g_shell_data->exit_code);
	}
	if (argc > 2)
	{
		ft_fprintf(STDERR_FILENO, "mishelle: exit: too many arguments\n");
		return (1);
	}
	nbr = ft_atoi(argv[1]);
	if (!nbr && *(argv[1]) != '0')
	{
		ft_fprintf(STDERR_FILENO,
			"mishelle: exit: %s: numeric argument required\n", argv[1]);
		free_and_exit(2);
	}
	ft_fprintf(STDOUT_FILENO, "mishelle: Exit o7\n");
	free_and_exit(nbr);
	return (0);
}
