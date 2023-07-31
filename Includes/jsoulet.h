/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jsoulet.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:26:37 by jsoulet           #+#    #+#             */
/*   Updated: 2023/07/29 13:29:06 by lolefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSOULET_H
# define JSOULET_H

# include "minishell.h"


int		check_line(t_par **par);
int		commande_len(t_par **par);
char	**create_commande(t_par **par, int i);
void	execute_cmd(t_env *env, t_rinity *cmd_struct);
char	*get_path(char *cmd, t_env *env);
char	*get_path_cmd(char **path, char *cmd);
void	piper(t_env *env, t_rinity *cmd_struct);
void	exec_last(t_env *env, t_rinity *cmd_struct, char **envp);
int		ft_heredoc(char *str);
/*int	create_fd_in(char **file_in, char **type_in);
int		append_file_content(char *file_in);
int		append_file_out_content(char *file, int option);
int		create_fd_out(char **file_out, char **type_out);
int		verif_in_out(t_rinity *cmd_struct, int *fd_in, int *fd_out);
void	close_and_dup_fd(int *fd_in, int *fd_out, int *fd);*/
void	redirect(t_rinity *cmd_struct, int option);
void	redirect_in(char **file_in, char **type_in);
void	redirect_out(char **file_out, char **type_out);

#endif
