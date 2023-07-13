/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:59:01 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/13 11:04:00 by lolefevr         ###   ########.fr       */
=======
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:59:01 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/13 12:36:21 by hnogared         ###   ########.fr       */
>>>>>>> 3a31d1f2bc5aa1bbde8ccb321a2e8615964643b9
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
		check_starterrors(line);
		ft_parsing(line);
	}
	return (0);
}
