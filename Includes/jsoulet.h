/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jsoulet.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:26:37 by jsoulet           #+#    #+#             */
/*   Updated: 2023/07/21 14:39:19 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSOULET_H
# define JSOULET_H

//#include "../Includes/minishell.h"


int		check_line(t_par **par);
int		commande_len(t_par **par);
char	**create_commande(t_par **par);
void	execute_cmd(t_env *env, t_rinity *cmd_struct);
char	*get_path(char *cmd, t_env *env);
char	*get_path_cmd(char **path, char *cmd);
void	piper(t_env *env, t_rinity *cmd_struct);
void	exec_last(t_env *env, t_rinity *cmd_struct);
int		create_fd_in(char **file_in, char **type_in, int fd_in);
int		append_file_content(char *file, int fd_in);
char	*ft_heredoc(char *str, int fd_in);

#endif
