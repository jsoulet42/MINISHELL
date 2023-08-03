#ifndef MDIAMANT_H
# define MDIAMANT_H

# include "get_next_line_bonus.h"

struct s_parsing
{
	char	*str;
	int		type;
};
struct s_par
{
	char	**command;
	char	**file_in;
	char	**file_out;
	char	**type_in;
	char	**type_out;
	char	**kafka;
	int		quote_type;
	int		builtin;
};

int			calc_size_type(char *str);
int			calc_type(char *str);
void		sparse(t_par **p, char *argv);
void		print_t_par(t_par **p);
int			get_skip_count(const char *str);
t_rinity	**ft_parsing(char *argv);
int			is_quote(char *argv);
int			is_quote_zero(char *argv);
int			verifquote(char *argv);
void		free_t_par(t_par **p);
int			is_operand(const char *str);
int			count_arg(const char *argv, int i);
int			strstr_len(char **str);
void		print_t_rinity(t_rinity **t);
int			count_cmd(t_par **par);
t_rinity	**t_rinity_init(t_par **p);
char		**new_neo(char *add);


char		**create_type_in(t_par **p, int i);
char		**create_type_out(t_par **p, int i);
char		**create_file_in(t_par **p, int i);
char		**create_file_out(t_par **p, int i);
char		**create_kafka(t_par **p, int i);
char		**str_tab_add_neo(char **str, char *add);
int			real_cmd(t_par **par);
int			next_pipe(t_par **p, int i);

/* Srcs/mdiamant/parsing_02.c */
/* Srcs/mdiamant/parsing_03.c */
/* Srcs/mdiamant/parsing_04.c */
/* Srcs/mdiamant/parsing_05.c */
/* Srcs/mdiamant/parsing_06.c */
/* Srcs/mdiamant/parsing_07.c */
/* Srcs/mdiamant/parsing_08.c */
int		ft_is_whitespace(char str);
char	*ft_split_utils(const char *s, int i, int start);



/* Srcs/mdiamant/parsing_09.c */

void		fusion_arg(char **line);
int			find_next_char(const char *str, const char c);




#endif
