/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:03:14 by hnogared          #+#    #+#             */
/*   Updated: 2023/09/04 17:34:00 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_parsing
{
	char	*str;
	int		type;
	int		fusion;
}		t_par;

int				commande_len(t_par **par);
int				next_good_commande(t_par **par, int i);
char			**create_commande(t_par **par, int i);
void			free_t_par(t_par **p);
void			sparse(t_par **p, char *argv);
void			print_t_par(t_par **p);

/* Srcs/simplquote_01.c */
int				simplquote(char *str);

/* Srcs/free_utils_02.c */
void			free_and_return(void);

/* Srcs/check_starterrors01.c */
int				doublequote(int *i, char *str);
int				simplequote( int *i, char *str);
unsigned char	error_quote(char *str);
void			error_dquote(char *str, int *dquote, int *i);
void			error_squote(char *str, int *squote, int *i);

/* srcs/parsing_02.c */
int				easy_quote(char **line);
int				hard_quote_01(char **line, int i, int j);
int				hard_quote_02(char **line);
void			easy_quote_utils(char **str);
void			fusion_arg(char **line);

/* srcs/parsing_04.c */
char			**create_file_in(char **line_tab);
char			**create_file_out(char **line_tab);
char			**create_kafka(char **line_tab);
char			**create_type_in(char **line_tab);
char			**create_type_out(char **line_tab);

/* Srcs/parsing_05.c */
int				calc_size_type(char *str);
int				calc_type(char *str);
int				is_operand(const char *str);
int				count_arg(const char *argv, int i);
int				get_skip_count(const char *str);

/* Srcs/parsing_06.c */
int				is_quote(char *argv);
int				is_quote_zero(char *argv);
int				verifquote(char *argv);

/* Srcs/parsing_07.c */
int				strstr_len(char **str);
void			ft_addchar(char **str, int i, char *c);

/* Srcs/parsing_08.c */
int				find_next_char(const char *str, const char c);
int				ft_is_whitespace(char str);

#endif
