/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hnogared.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:59:11 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/14 02:42:25 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HNOGARED_H
# define HNOGARED_H

/* open */
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

/* Prompt string buffer size */
# define PROMPT_BUFFER	255

/* Startup environment variables */
# define START_VAR_AMOUNT	1
# define START_PATH	":./bin"

/* Environment variable update modes */
# define SH_OVERWRITE	0
# define SH_CONCAT		1

typedef struct t_env
{
	char	*name;
	char	*value;
	char	*display;
	void	*next;
}				t_env;

/* Srcs/hnogared/utils_01.c */
void	safe_free(void **ptr_addr);

/* Srcs/hnogared/prompt_01.c */
char	*prompt(void);

/* Srcs/hnogared/environment_01.c */
t_env	*init_env(t_env **env_list, char **envp);
void	print_str_tab(char **str_tab);
void	free_str_tab(char **str_tab);

/* Srcs/hnogared/environment_utils_01.c */
t_env	*new_env_var(char *var_str, void *next);
t_env	*env_add_back(t_env **env_list, t_env *new);
void	print_env(t_env *env_list);
void	del_env_var(t_env *env_var, t_env *prev_var, t_env *next_var);
void	free_env(t_env **env_list);

/* Srcs/hnogared/environment_utils_02.c */
t_env	*get_env_var(t_env *env_list, char *var_name);
t_env	*update_env_var(t_env *env_var, char *value, int mode);

#endif
