/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lolefevr.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:05:36 by lolefevr          #+#    #+#             */
/*   Updated: 2023/08/02 13:55:50 by lolefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
t_env	*ft_cd(int argc, char **argv, t_env **env);
int		lentab(char **tableau);
void	modif_shlvl(char **env);
void	new_shlvl(char *env);
void	ft_exit();
char	**env_update(char **envp, t_shell *env);
t_env	*update_pwd(char *oldpwd, char *pwd, t_env **env);
int		ft_env(t_env *env);
void	ft_pwd();
int		ft_echo(int argc, char **argv);

#endif
