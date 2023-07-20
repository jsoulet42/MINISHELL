/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:45:13 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/20 13:10:11 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	sig_handler(int signal)
{
	if (signal != SIGINT)
		return ;
	ft_fprintf(STDERR_FILENO, "\n");
}
