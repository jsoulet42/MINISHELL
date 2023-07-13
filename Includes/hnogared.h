/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hnogared.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:39:49 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/13 18:48:12 by hnogared         ###   ########.fr       */
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
# define START_PATH	"bin"

typedef struct t_env
{
	char	*var_name;
	char	*var_val;
	char	*var_display;
	void	*next;
}				t_env;

/* Srcs/hnogared/prompt_01.c */
char	*prompt(void);

/* Srcs/hnogared/environment_01.c */
t_env	*add_env_variable(t_env *env_list, char *var_name, char *var_value);
t_env	*init_env(t_env **env_list, char **envp);
void	print_str_tab(char **str_tab);
void	free_str_tab(char **str_tab);

/* Srcs/hnogared/environment_utils_01.c */
t_env	*env_add_back(t_env **env_list, t_env *new);
t_env	*new_env_var(char *var_str, void *next);
void	print_env(t_env *env_list);
void	del_env_var(t_env *env_var, t_env *prev_var, t_env *next_var);
void	free_env(t_env **env_list);

#endif
