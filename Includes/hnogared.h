/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hnogared.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:44:06 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/17 12:32:09 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HNOGARED_H
# define HNOGARED_H

# include "minishell.h"

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
# define START_VAR_AMOUNT	1
# define START_PATH	"./bin:"

/* Environment variable update modes */
# define SH_OVERWRITE	0
# define SH_ADDBACK		1
# define SH_ADDFRONT	2

/* Environment display mode */
# define SH_UNORDERED	0
# define SH_ORDERED		1

/* Comparative macros */
# define SH_SET(dst, src)	__typeof__ (src) dst = (src)
# define SH_MAX(a, b)	({SH_SET(_a, a); SH_SET(_b, b); _a > _b ? _a : _b;})
# define SH_MIN(a, b)	({SH_SET(_a, a); SH_SET(_b, b); _a < _b ? _a : _b;})

struct s_env
{
	char	*name;
	char	*value;
	char	*display;
	void	*next;
};

/* Srcs/builtins */
int		ft_export(char **argv, t_env *env);

/* Srcs/hnogared/utils_01.c */
char	**order_str_tab(char **str_tab, char limit);
void	safe_free(void **ptr_addr);
void	print_str_tab(char **str_tab);
void	free_str_tab(char **str_tab);
void	free_data(t_shell *shell_data);

/* Srcs/hnogared/prompt_01.c */
char	*prompt(void);

/* Srcs/hnogared/init_environment_01.c */
t_env	*init_env(t_env **env_list, char **envp);

/* Srcs/hnogared/environment_utils_01.c */
char	*ft_getenv(t_env *env, char *var_name);
t_env	*new_env_var(char *var_str, void *next);
t_env	*env_add_back(t_env **env_list, t_env *new);
void	del_env_var(t_env *env_var, t_env *prev_var, t_env *next_var);
void	free_env(t_env **env_list);

/* Srcs/hnogared/environment_utils_02.c */
char	**env_to_str_tab(t_env *env_list);
t_env	*get_env_var(t_env *env_list, char *var_name);
t_env	*update_env_var(t_env *env_var, char *value, int mode);
void	print_env(t_env *env_list, int mode);

#endif
