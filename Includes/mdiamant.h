/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mdiamant.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:28:43 by mdiamant          #+#    #+#             */
/*   Updated: 2023/07/14 16:19:09 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MDIAMANT_H
# define MDIAMANT_H

struct s_parsing
{
	char	*str;
	int		type;
	int		quote_type;
}				t_par;

int		calc_size_type(char *str);
int		calc_type(char *str);
void	sparse(t_par **p, char *argv);
void	print_t_par(t_par **p);
int		get_skip_count(const char *str);
int		is_quote(char *argv);
int		verifquote(char *argv);
void	free_t_par(t_par **p);
int		is_operand(const char *str);
int		count_arg(const char *argv);
t_par	ft_parsing(char *argv);

void	error_exit(char *str);

void	test_dup(t_par **p);

#endif
