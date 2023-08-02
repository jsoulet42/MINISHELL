#ifndef HNOGARED_H
# define HNOGARED_H

# include "minishell.h"

/* History management */
# include <readline/history.h>

/* open */
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

/* Status codes for function returns */
# define SH_SUCCESS	0
# define SH_ERROR	1

/* Prompt string buffer size */
# define PROMPT_BUFFER	255

/* Startup environment variables */
# define START_PATH		"PATH=./bin:"
# define START_LOGNAME	"LOGNAME=guest"
# define START_NAME		"NAME=mishelle"

/* Environment variable update modes */
# define SH_OVERWRITE	0
# define SH_ADDBACK		1
# define SH_ADDFRONT	2

/* Environment display mode */
# define SH_DISORDERED	0
# define SH_ORDERED		1

/* Termios setup modes */
# define TERMIOS_UNMUTE_CTRL	0
# define TERMIOS_MUTE_CTRL		1

/* Comparative macros */
//# define SH_SET(dst, src)	__typeof__ (src) dst = (src)
//# define SH_MAX(a, b)	({SH_SET(_a, a); SH_SET(_b, b); _a > _b ? _a : _b;})
//# define SH_MIN(a, b)	({SH_SET(_a, a); SH_SET(_b, b); _a < _b ? _a : _b;})

/* Undeclared arrays macros */
//# define INT_TAB(...)	(int []){__VA_ARGS__}
//# define STR_TAB(...)	(char *[]){__VA_ARGS__}

struct s_env
{
	char	*name;
	char	*value;
	char	*display;
	void	*prev;
	void	*next;
};

/* Srcs/builtins */
int		ft_export(char **argv, t_env **env);
int		ft_unset(char **argv, t_env **env);

/* Srcs/hnogared/free_utils_01.c */
void	safe_free(void **ptr_addr);
void	free_str_tab(void **str_tab);
void	free_data(t_shell *shell_data);
void	free_and_exit(void);
void	free_trinity(void);

/* Srcs/hnogared/free_utils_02.c */
void	free_and_return(void);

/* Srcs/hnogared/utils_01.c */
char	*ft_strjoin_plus(char *dest, char *src);
char	*ft_free_strcat(char **dest, char *src, int start, int end);
char	**order_str_tab(char **str_tab, char limit);

/* Srcs/hnogared/display_01.c */
int		set_termios_mode(int mode);
char	*prompt(t_env *env);

/* Srcs/hnogared/init_environment_01.c */
t_env	*init_env(t_env **env_list, char **envp);

/* Srcs/hnogared/environment_utils_01.c */
char	*ft_getenv(t_env *env, char *var_name);
t_env	*new_env_var(char *var_str, void *prev, void *next);
t_env	*env_add_back(t_env **env_list, t_env *new);
void	del_env_var(t_env *env_var, t_env *prev_var, t_env *next_var);
void	free_env(t_env **env_list);

/* Srcs/hnogared/environment_utils_02.c */
char	**env_to_str_tab(t_env *env_list);
t_env	*get_env_var(t_env *env_list, char *var_name);
t_env	*update_env_var(t_env *env_var, char *value, int mode);
void	print_env(t_env *env_list, int mode);

/* Srcs/hnogared/environment_utils_03.c */
int		get_dollar_value(char **to_set, char *to_search, t_env *env);
char	*expand_dollars(char *str, t_env *env);

/* Srcs/hnogared/signals.c */
void	main_sig_handler(int signal);
void	parent_sig_handler(int signal);


#endif
