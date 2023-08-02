#ifndef LOLEFEVR_H
# define LOLEFEVR_H

# include "minishell.h"

int		check_starterrors(char *str);
int		error_pipe(char *str);
int		error_gen(char *str, int i);
int		error_quote(char *str);
void	error_squote(char *str, int *squote, int *i);
void	error_dquote(char *str, int *dquote, int *i);
void	dblequote(int *i, char *str);
void	simplequote( int *i, char *str);
int		viveldop(int gel, char *str, int *i);
int		unknown_command();
int		change_directory(const char *path);
char	*go_home(char **env);
void	ft_cd(int argc, char **argv, t_env *env);
int		lentab(char **tableau);
void	signal_c(int signal);
void	signal_d(int signal);
void	init_signal(void);

#endif
