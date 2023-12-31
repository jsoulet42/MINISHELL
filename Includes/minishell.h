/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:07:30 by jsoulet           #+#    #+#             */
/*   Updated: 2023/09/21 14:40:05 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

# include <readline/history.h>
# include <readline/readline.h>

# include <term.h>
# include <termios.h>
# include <curses.h>

# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>

# include "libft.h"
# include "minishell_macros.h"
# include "get_next_line_bonus.h"

extern struct s_shell	g_shell_data;

typedef struct termios	t_termios;

typedef struct s_rinity
{
	int		builtin;
	char	*cmd_path;
	char	**cmd;
	char	**file_in;
	char	**file_out;
	char	**type_in;
	char	**type_out;
}		t_rinity;

typedef struct s_env
{
	char	*name;
	char	*value;
	char	*display;
	void	*prev;
	void	*next;
}		t_env;

typedef struct s_shell
{
	int			in;
	int			out;
	int			exit_code;
	t_env		*env;
	t_rinity	**t;
	t_termios	default_termios;
}				t_shell;

/* *********************************** */
/* Srcs/builtins                       */
/* *********************************** */
int				ft_cd(int argc, char **argv, t_env **env);
int				ft_echo(int argc, char **argv);
int				ft_env(int argc, char **argv, t_env **env);
int				ft_exit(int argc, char **argv);
int				export_var(char *arg, t_env **env, int mode);
int				ft_export(char **argv, t_env **env);
int				ft_pwd(int argc, char **argv);
int				ft_unset(char **argv, t_env **env);

/* *********************************** */
/* Srcs/display                        */
/* *********************************** */
/* debug_display.c */
void			print_t_rinity(t_rinity **t);

/* display.c */
int				set_termios_mode(int mode, t_termios termios_struct);
char			*prompt(t_env *env);
void			ft_perror(const char *prefix, const char *prefix2);

/* *********************************** */
/* Srcs/environment                    */
/* *********************************** */
/* environment_utils_01.c */
t_env			*new_env_var(char *var_str, void *prev, void *next);
t_env			*env_add_back(t_env **env_list, t_env *new);
t_env			*update_env_var(t_env *env_var, char *value, int mode);
void			del_env_var(t_env *env_var, t_env *prev_var, t_env *next_var);

/* environment_utils_02.c */
char			*ft_getenv(t_env *env, char *var_name);
char			**env_to_str_tab(t_env *env_list);
t_env			*get_env_var(t_env *env_list, char *var_name);
void			print_env(t_env *env_list, int mode);
void			free_env(t_env **env_list);

/* init_environment.c */
t_env			*init_env(t_env **env_list, char **envp);

/* *********************************** */
/* Srcs/interpret                      */
/* *********************************** */
/* ft_heredoc.c */
int				ft_heredoc(char *str);

/* get_path.c */
char			*get_path(char *cmd, t_env *env);

/* interpret_01.c */
void			piper(t_env *env, t_rinity *cmd_struct);
void			exec_last(t_env *env, t_rinity *cmd);

/* interpret_02.c */
int				agent_smith(char *cmd);
int				execute_builtin(t_rinity *cmd_struct);
void			execute_cmd(t_env *env, t_rinity *cmd_struct);
void			get_exit_code(int status_code, int *to_set);

/* redirect_streams.c */
int				redirect_in(char **file_in, char **type_in);
int				redirect_out(char **file_out, char **type_out);
int				redirect_streams(t_rinity *cmd_struct);

/* *********************************** */
/* Srcs/parsing                        */
/* *********************************** */
/* check_starterrors.c */
int				check_starterrors(char *str);

/* expand_dollars.c */
char			*expand_dollars(char *str, t_env *env);

/* expand_line.c */
char			**expand_line(char *line, t_env *env);

/* parsing_01.c */
t_rinity		**ft_parsing(char *argv);
t_rinity		**t_rinity_init(char **line_tab);

/* parsing_02.c */
int				check_line_words(const char **line_tab);
int				next_pipe(char **line_tab);
int				real_cmd(char **line_tab);
int				doublequote(int *i, char *str);
int				simplequote(int *i, char *str);

/* *********************************** */
/* Srcs/signals                        */
/* *********************************** */
/* Srcs/signals.c */
void			main_sig_handler(int signal);
void			heredoc_sig_handler(int signal);
void			parent_sig_handler(int signal);

/* *********************************** */
/* Srcs/utils                          */
/* *********************************** */
/* free_utils.c */
void			safe_free(void **ptr_addr);
void			free_str_tab(void **str_tab);
void			free_data(t_shell shell_data);
void			free_trinity_struct(t_rinity *t);
void			free_trinity_tab(t_rinity ***t);

/* str_tab_utils_01.c */
int				str_tab_len(char **str);
int				print_str_tab(int fd, char **str_tab);
char			**new_neo(char *add);
char			**str_tab_add_neo(char **str, char *add);
char			**order_str_tab(char **str_tab, char limit);

/* str_tab_utils_02.c */
char			*ft_free_strcat(char **dest, char *src);
char			*ft_strjoin_plus(char *dest, char *src);
char			*join_str_tab(const char **str_tab);
char			**ft_fsplit(char *str, int (*word_len_counter)(char *str));

/* utils.c */
int				ft_min(int a, int b);
int				ft_isoperand(char c);
int				ft_is_whitespace(char c);
int				ft_strccmp(const char *str1, const char *str2, char limit);
char			*ft_strchrnul(const char *str, int c);

#endif
