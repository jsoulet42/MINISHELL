/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mdiamant.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:28:43 by mdiamant          #+#    #+#             */
/*   Updated: 2023/07/13 17:58:13 by lolefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_parsing
{
	char	*str;
	int		type; //0 = string, 1 = operand, 2 = option, 3 = variable, 4 = num
}				t_par;

void free_t_par(t_par **p);
int	verifquote(char *argv);
