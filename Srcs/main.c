/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:59:01 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/13 18:03:32 by lolefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	main(void)
{
	char	*line;
	char	*line2;

	while (1)
	{
		line = prompt();
		if (!line)
			break ;
		line2 = ft_strtrim(line, " \n\t\v");
		free(line);
		if (check_starterrors(line2) > 0)
			return (0);
		ft_parsing(line2);
	}
	return (0);
}
