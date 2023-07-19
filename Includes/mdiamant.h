/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mdiamant.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:28:43 by mdiamant          #+#    #+#             */
/*   Updated: 2023/07/19 16:11:54 by lolefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MDIAMANT_H
# define MDIAMANT_H

# include "get_next_line_bonus.h"

struct s_parsing
{
	char	*str;
	int		type;
	int		quote_type;
	int		command_elem_id;
};
struct s_par
{
	char	**commande;
	char	*file;
	int		quote_type;
};

int		calc_size_type(char *str);
int		calc_type(char *str);
void	sparse(t_par **p, char *argv);
void	print_t_par(t_par **p);
int		get_skip_count(const char *str);
t_par	**ft_parsing(char *argv);
int		is_quote(char *argv);
int		verifquote(char *argv);
void	free_t_par(t_par **p);
int		is_operand(const char *str);
int		count_arg(const char *argv);
void	command_nb(t_par **p);


void	error_exit(char *str);

void	test_dup(t_par **p);

#endif
