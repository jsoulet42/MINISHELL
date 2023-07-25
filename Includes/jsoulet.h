/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jsoulet.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:26:37 by jsoulet           #+#    #+#             */
/*   Updated: 2023/07/19 15:47:17 by lolefevr         ###   ########.fr       */
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
void	exec_last(t_env *env, t_rinity *cmd_struct);
int		create_fd_in(char **file_in, char **type_in);
int		append_file_content(char *file_in);
int		ft_heredoc(char *str);

#endif
