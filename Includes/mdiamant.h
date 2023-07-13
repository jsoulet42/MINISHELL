/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mdiamant.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:28:43 by mdiamant          #+#    #+#             */
/*   Updated: 2023/07/13 17:23:54 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_parsing
{
	char	*str;
	int		type; //0 = string, 1 = operand, 2 = option, 3 = variable, 4 = num
}				t_par;

int		calc_size_type(char *str);
int		calc_type(char *str);
void	sparse(t_par **p, char *argv);
void	print_t_par(t_par **p);
int		get_skip_count(const char *str);
void	ft_parsing(char *argv);
int		is_quote(char *argv);
int		verifquote(char *argv);
void	free_t_par(t_par **p);
