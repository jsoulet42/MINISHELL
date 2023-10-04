/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:10:40 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/15 17:00:23 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	ft_pwd(int argc, char **argv)
{
	char	buffer[512];

	(void)argc;
	(void)argv;
	if (getcwd(buffer, sizeof(buffer)) != NULL)
		ft_printf("Le répertoire de travail actuel est : %s\n", buffer);
	else
	{
		ft_fprintf(STDERR_FILENO, "Erreur lors de l'appel à getcwd");
		return (1);
	}
	return (0);
}
