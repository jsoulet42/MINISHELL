/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:06:11 by lolefevr          #+#    #+#             */
/*   Updated: 2023/08/04 22:18:52 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	ft_pwd(int argc, char **argv)
{
	(void)argc;
	(void)argv;
    char buffer[512];

    if (getcwd(buffer, sizeof(buffer)) != NULL)
        printf("Le répertoire de travail actuel est : %s\n", buffer);
	else
	{
        perror("Erreur lors de l'appel à getcwd");
        return (1);
    }
	return (0);
}
