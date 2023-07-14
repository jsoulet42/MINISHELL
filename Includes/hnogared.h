/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hnogared.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:59:11 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/14 16:09:11 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HNOGARED_H
# define HNOGARED_H

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
# define START_PATH	":./bin"

/* Environment variable update modes */
# define SH_OVERWRITE	0
# define SH_CONCAT		1

typedef struct s_env
{
	char	*name;
	char	*value;
	char	*display;
	void	*next;
}				t_env;

/* Srcs/hnogared/utils_01.c */
void	safe_free(void **ptr_addr);
void	print_str_tab(char **str_tab);
void	free_str_tab(char **str_tab);

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
t_env	*get_env_node(t_env *env_list, char *var_name);
t_env	*update_env_var(t_env *env_var, char *value, int mode);
void	print_env(t_env *env_list);

#endif
