/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:07:30 by jsoulet           #+#    #+#             */
/*   Updated: 2023/09/04 14:50:37 by hnogared         ###   ########.fr       */
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

extern struct s_shell	*g_shell_data;

typedef struct s_parsing
{
	char	*str;
	int		type;
	int		fusion;
}		t_par;

typedef struct s_par
{
	char	**cmd;
	char	**file_in;
	char	**file_out;
	char	**type_in;
	char	**type_out;
	char	**kafka;
	int		quote_type;
	int		builtin;
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
	t_par			**par;
	t_env			*env;
	t_rinity		**t;
	int				in;
	int				out;
	int				fd[2];
	int				exit_code;
	char			*path;
	char			*pwd;
}				t_shell;

/* Srcs/builtins */
int				ft_echo(int argc, char **argv);
int				ft_env(int argc, char **argv, char **env);
int				ft_export(char **argv, t_env **env);
int				ft_pwd(int argc, char **argv);
int				ft_unset(char **argv, t_env **env);
int				ft_exit(int argc, char **argv);

/* Srcs/builtins/ft_cd.c */
//int				change_directory(const char *path);
int				ft_cd(int argc, char **argv, t_env **env);
//t_env			*update_pwd(char *oldpwd, char *pwd, t_env **env);

/* Srcs/check_starterrors01.c */
int				doublequote(int *i, char *str);
int				simplequote( int *i, char *str);
//unsigned char	error_quote(char *str);
void			error_dquote(char *str, int *dquote, int *i);
void			error_squote(char *str, int *squote, int *i);

/* Srcs/check_starterrors02.c */
int				check_starterrors(char *str);
//int				error_gen(char *str, int i);
//int				error_pipe(char *str);
int				unknown_command(void);
//int				viveldop(char gel, char *str, int *i);

/* Srcs/display.c */
int				set_termios_mode(int mode);
char			*prompt(t_env *env);
void			ft_perror(const char *prefix, const char *prefix2);

/* Srcs/doublquote_01.c */
int				doublquote(char *str);

/* Srcs/environment_utils_01.c */
char			*ft_getenv(t_env *env, char *var_name);
t_env			*env_add_back(t_env **env_list, t_env *new);
t_env			*new_env_var(char *var_str, void *prev, void *next);
void			del_env_var(t_env *env_var, t_env *prev_var, t_env *next_var);
void			free_env(t_env **env_list);

/* Srcs/environment_utils_02.c */
char			**env_to_str_tab(t_env *env_list);
t_env			*get_env_var(t_env *env_list, char *var_name);
t_env			*update_env_var(t_env *env_var, char *value, int mode);
void			print_env(t_env *env_list, int mode);

/* Srcs/expand_dollars.c */
char			*expand_dollars(char *str, t_env *env);

/* Srcs/expand_line.c */
char			**expand_line(char *line, t_env *env);

/* Srcs/free_utils_01.c */
void			safe_free(void **ptr_addr);
void			free_str_tab(void **str_tab);
void			free_data(t_shell *shell_data);
void			free_trinity_struct(t_rinity *t);
void			free_trinity_tab(t_rinity **t);

/* Srcs/free_utils_02.c */
void			free_and_return(void);

/* Srcs/ft_heredoc.c */
int				ft_heredoc(char *str);

/* Srcs/init_environment.c */
char			*ft_pwd2(void);
char			*modif_pwd(void);
char			*modif_pwd2(void);
t_env			*init_env(t_env **env_list, char **envp);

/* Srcs/interpret_01.c */
//int				check_line(t_par **par);
int				check_line_words(const char **line_tab);
int				commande_len(t_par **par);
int				next_good_commande(t_par **par, int i);
char			**create_commande(t_par **par, int i);
void			execute_cmd(t_env *env, t_rinity *cmd_struct);

/* Srcs/interpret_02.c */
int				redirect_in(char **file_in, char **type_in);
int				redirect_out(char **file_out, char **type_out);
int				redirect_streams(t_rinity *cmd_struct);

/* Srcs/interpret_03.c */
int				piper(t_env *env, t_rinity *cmd_struct);
char			*get_path(char *cmd, t_env *env);
void			run_child(t_rinity *cmd_struct, int *fd, t_env *env);

/* Srcs/interpret_04.c */
int				agent_smith(char *cmd);
int				execute_builtin(t_rinity *cmd_struct, int builtin);
void			exec_last(t_env *env, t_rinity *cmd_struct, char **envp);
void			get_exit_code(int status_code, int *to_set);

/* Srcs/lentab.c */
int				lentab(char **tableau);
char			**env_update(char **envp, t_shell *env);

/* Srcs/main.c */
int				prompt_cmd_02(char *line2, char **envp);

/* Srcs/modif_shlvl.c */
void			modif_shlvl(char **env);
void			new_shlvl(char *env);

/* srcs/parsing_01.c */
t_rinity		**ft_parsing(char *argv);
t_rinity		**t_rinity_init(char **line_tab);

/* srcs/parsing_02.c */
int				easy_quote(char **line);
int				hard_quote_01(char **line, int i, int j);
int				hard_quote_02(char **line);
void			easy_quote_utils(char **str);
void			fusion_arg(char **line);

/* srcs/parsing_03.c */
void			print_t_rinity(t_rinity **t);

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
int				next_pipe(char **line_tab);
int				real_cmd(char **line_tab);
int				verifquote(char *argv);

/* Srcs/parsing_07.c */
int				strstr_len(char **str);
char			**new_neo(char *add);
char			**str_tab_add_neo(char **str, char *add);
void			free_t_par(t_par **p);
void			ft_addchar(char **str, int i, char *c);

/* Srcs/parsing_08.c */
int				find_next_char(const char *str, const char c);
int				ft_is_whitespace(char str);
void			sparse(t_par **p, char *argv);

/* Srcs/signals.c */
void			main_sig_handler(int signal);
void			heredoc_sig_handler(int signal);
void			parent_sig_handler(int signal);

/* Srcs/simplquote_01.c */
int				simplquote(char *str);

/* Srcs/utils_01.c */
int				ft_strccmp(const char *str1, const char *str2, char limit);
char			*ft_free_strcat(char **dest, char *src, int start, int end);
char			*ft_strjoin_plus(char *dest, char *src);
char			**order_str_tab(char **str_tab, char limit);
void			print_str_tab(char **str_tab);
void			print_t_par(t_par **p);

/* Srcs/utils_02.c */
char			*ft_strchrnul(const char *str, int c);
char			*join_str_tab(const char **str_tab);
char			*join_str_tab_mono(const char **str_tab);
char			**ft_keep_split(char *str, char sep);

/* Srcs/utils_03.c */
int				ft_min(int a, int b);
int				ft_isoperand(char c);
char			**ft_fsplit(char *str, int (*word_len_counter)(char *str));
void			ft_supprchar(char **str, int i);

#endif
