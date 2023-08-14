/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:07:30 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/14 20:44:44 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
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
# include <errno.h>
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
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

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

int				doublquote(char *str);
int				simplquote(char *str);
void			print_str_tab(char **str_tab);
int				ft_export(char **argv, t_env **env);
int				ft_unset(char **argv, t_env **env);
void			safe_free(void **ptr_addr);
void			free_str_tab(void **str_tab);
void			free_data(t_shell *shell_data);
void			free_and_exit(void);
void			free_trinity(void);
void			free_and_return(void);
char			*ft_strjoin_plus(char *dest, char *src);
char			*ft_free_strcat(char **dest, char *src, int start, int end);
int				set_termios_mode(int mode);
char			*prompt(t_env *env);
t_env			*init_env(t_env **env_list, char **envp);
char			*ft_getenv(t_env *env, char *var_name);
t_env			*new_env_var(char *var_str, void *prev, void *next);
t_env			*env_add_back(t_env **env_list, t_env *new);
void			del_env_var(t_env *env_var, t_env *prev_var, t_env *next_var);
void			free_env(t_env **env_list);
char			**env_to_str_tab(t_env **env_list);
t_env			*get_env_var(t_env *env_list, char *var_name);
t_env			*update_env_var(t_env *env_var, char *value, int mode);
int				get_dollar_value(char **to_set, char *to_search, t_env *env);
char			*expand_dollars(char *str, t_env *env);
void			main_sig_handler(int signal);
void			parent_sig_handler(int signal);
void			second_sig_handler(int signal);
int				calc_size_type(char *str);
int				calc_type(char *str);
void			sparse(t_par **p, char *argv);
void			print_t_par(t_par **p);
int				get_skip_count(const char *str);
t_rinity		**ft_parsing(char *argv);
int				is_quote(char *argv);
int				is_quote_zero(char *argv);
int				verifquote(char *argv);
void			free_t_par(t_par **p);
int				is_operand(const char *str);
int				count_arg(const char *argv, int i);
int				strstr_len(char **str);
void			print_t_rinity(t_rinity **t);
t_rinity		**t_rinity_init(t_par **p);
char			**new_neo(char *add);
char			**create_type_in(t_par **p, int i);
char			**create_type_out(t_par **p, int i);
char			**create_file_in(t_par **p, int i);
char			**create_file_out(t_par **p, int i);
char			**create_kafka(t_par **p, int i);
char			**str_tab_add_neo(char **str, char *add);
int				real_cmd(t_par **par);
int				next_pipe(t_par **p, int i);
int				ft_is_whitespace(char str);
void			fusion_arg(char **line);
int				find_next_char(const char *str, const char c);
void			ft_supprchar(char **str, int i);
void			easy_quote_utils(char **str);
void			ft_addchar(char **str, int i, char *c);
int				easy_quote(char **line);
int				hard_quote_01(char **line, int i, int j);
int				hard_quote_02(char **line);
int				check_starterrors(char *str);
int				error_pipe(char *str);
int				error_gen(char *str, int i);
int				error_quote(char *str);
void			error_squote(char *str, int *squote, int *i);
void			error_dquote(char *str, int *dquote, int *i);
void			dblequote(int *i, char *str);
void			simplequote( int *i, char *str);
int				viveldop(char gel, char *str, int *i);
int				unknown_command(void);
int				change_directory(const char *path);
t_env			*ft_cd(int argc, char **argv, t_env **env);
int				lentab(char **tableau);
void			modif_shlvl(char **env);
void			new_shlvl(char *env);
void			ft_exit(void);
char			**env_update(char **envp, t_shell *env);
t_env			*update_pwd(char *oldpwd, char *pwd, t_env **env);
int				ft_env(int argc, char **argv, char **env);
int				ft_pwd(int argc, char **argv);
int				ft_echo(int argc, char **argv);
int				check_line(t_par **par);
int				commande_len(t_par **par);
char			**create_commande(t_par **par, int i);
void			execute_cmd(t_env *env, t_rinity *cmd_struct);
char			*get_path(char *cmd, t_env *env);
char			*get_path_cmd(char **path, char *cmd);
void			piper(t_env *env, t_rinity *cmd_struct);
void			exec_last(t_env *env, t_rinity *cmd_struct, char **envp);
int				ft_heredoc(char *str);
void			redirect(t_rinity *cmd_struct, int option);
void			redirect_in(char **file_in, char **type_in);
void			redirect_out(char **file_out, char **type_out);
char			*ft_pwd2(void);
char			*modif_pwd(void);
char			*modif_pwd2(void);
void			execute_builtin(t_rinity *cmd_struct, int builtin);
int				execute_first_builtin(t_rinity *cmd_struct, int builtin);
int				agent_smith(char *cmd);
void			execute_builtin2(t_rinity *cmd_struct, int builtin, t_env *env);
void			continue_child(t_rinity *cmd_struct, int *fd, t_env *env);
int				prompt_cmd_02(char *line2, char **envp);
int				next_good_commande(t_par **par, int i);
void			continue_child_builtin(t_rinity *cd, int builtin);
char			**env_to_str_tab_02(char **envp, t_env *start);
struct s_doll	init_doll(void);
void			print_env(t_env *env_list, int mode);
char			**order_str_tab(char **str_tab, char limit);

#endif
