/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jsoulet.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:26:37 by jsoulet           #+#    #+#             */
/*   Updated: 2023/07/31 14:16:50 by jsoulet          ###   ########.fr       */
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
int		ft_heredoc(char *str);
void	redirect(t_rinity *cmd_struct, int option);
void	redirect_in(char **file_in, char **type_in);
void	redirect_out(char **file_out, char **type_out);

#endif
