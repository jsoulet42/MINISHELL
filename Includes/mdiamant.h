/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mdiamant.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:28:43 by mdiamant          #+#    #+#             */
/*   Updated: 2023/07/27 16:29:00 by mdiamant         ###   ########.fr       */
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
};
struct s_par //t_rinity: file.txt < cat file
{
	char	**command;
	char	**file_in;
	char	**file_out;
	char	**type_in; // << <
	char	**type_out;// >> >
	char	**kafka;// char ** qui contient >> << < >
	char	*file;
	int		quote_type;
};

int			calc_size_type(char *str);
int			calc_type(char *str);
void		sparse(t_par **p, char *argv);
void		print_t_par(t_par **p);
int			get_skip_count(const char *str);
t_rinity	**ft_parsing(char *argv);
int			is_quote(char *argv);
int			verifquote(char *argv);
void		free_t_par(t_par **p);
int			is_operand(const char *str);
int			count_arg(const char *argv);
int			strstr_len(char **str);
void		print_t_rinity(t_rinity **t);
int			count_cmd(t_par **par);
t_rinity	**t_rinity_init(t_par **p);

char		**create_type_in(t_par **p, int i);
char		**create_type_out(t_par **p, int i);
char		**create_file_in(t_par **p, int i);
char		**create_file_out(t_par **p, int i);
char		**create_kafka(t_par **p, int i);
char		**str_tab_add_neo(char **str, char *add);
int			real_cmd(t_par **par);
int			next_pipe(t_par **p, int i);

char *prev_line(char *line, int i);




void	error_exit(char *str);

#endif
