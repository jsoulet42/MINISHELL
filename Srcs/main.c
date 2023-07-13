/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:59:01 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/13 12:36:21 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	main(void)
{
	char	*line;

	while (1)
	{
		line = prompt();
		if (!line)
			break ;
		ft_parsing(line);
	}
	return (0);
}
