/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:18:20 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/12 15:37:18 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Error: Wrong number of arguments\n");
		return (0);
	}
	ft_parsing(argv[1]);
	return (0);
}
