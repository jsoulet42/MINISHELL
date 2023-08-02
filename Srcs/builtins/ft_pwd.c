/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:06:11 by lolefevr          #+#    #+#             */
/*   Updated: 2023/08/02 12:26:26 by lolefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	ft_pwd()
{
    char buffer[512];

    if (getcwd(buffer, sizeof(buffer)) != NULL)
        printf("Le répertoire de travail actuel est : %s\n", buffer);
	else
	{
        perror("Erreur lors de l'appel à getcwd");
        return ;
    }
}
