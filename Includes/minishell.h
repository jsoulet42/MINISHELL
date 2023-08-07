#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <termios.h>
#include <errno.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <sys/types.h>
# include <termios.h>
# include <curses.h>
# include <errno.h>
# include <term.h>

# include "minishell_macros.h"

typedef struct s_parsing t_par;
typedef struct s_env t_env;
typedef struct s_par t_rinity;

typedef struct s_shell
{
	t_par		**par;
	t_env		*env;
	t_rinity	**t;
	int 		in;
	int 		out;
	int 		fd[2];
	char		*path;
	char		*pwd;
}				t_shell;

extern t_shell *g_shell_data;

# include "mdiamant.h"

int			calc_size_type(char *str);
int			calc_type(char *str);
t_par		**sparse(char *argv);
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
int			tparlen(t_par **p);
t_par		**fusion_sparse(t_par **p);
char		*fusion_sparse_utils(t_par **p, int *i);
t_par		*sparse_utils_01(char *argv, int *i, int *size);
t_par		*sparse_utils_02(char *argv, int *i, int *size);
t_par		**t_par_init(int len);
int			ft_is_whitespace(char str);
# include "hnogared.h"
# include "lolefevr.h"
# include "jsoulet.h"
# include "hnogared.h"

/*-----------------Srcs/lolefevr/doublquote_01.c-----------------*/
int		doublquote(char *str);

/*-----------------Srcs/lolefevr/simplquote_01.c-----------------*/
int		simplquote(char *str);

void	print_str_tab(char **str_tab);

#endif
