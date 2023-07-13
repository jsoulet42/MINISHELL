/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mdiamant.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:28:43 by mdiamant          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/07/12 19:07:03 by lolefevr         ###   ########.fr       */
=======
/*   Updated: 2023/07/13 09:18:07 by mdiamant         ###   ########.fr       */
>>>>>>> 3a31d1f2bc5aa1bbde8ccb321a2e8615964643b9
/*                                                                            */
/* ************************************************************************** */

typedef struct s_parsing
{
	char	*str;
	int		type; //0 = string, 1 = operand, 2 = option, 3 = variable, 4 = num
}				t_par;

void free_t_par(t_par **p);
int	verifquote(char *argv);
