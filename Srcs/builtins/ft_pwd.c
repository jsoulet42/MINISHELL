/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:10:40 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/07 15:34:52 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	ft_pwd(int argc, char **argv)
{
	char	buffer[512];

	(void)argc;
	(void)argv;
	if (getcwd(buffer, sizeof(buffer)) != NULL)
		printf("Le répertoire de travail actuel est : %s\n", buffer);
	else
	{
		perror("Erreur lors de l'appel à getcwd");
		return (1);
	}
	return (0);
}
