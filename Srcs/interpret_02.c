/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:16:19 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/24 18:12:44 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static int	handle_in_file(char *file_in, char *type_in)
{
	int	fd_in;

	fd_in = -1;
	if (ft_strncmp(type_in, "<<", 3) == 0)
	{
		fd_in = ft_heredoc(file_in);
		if (fd_in < 0)
			return (SH_ERROR);
	}
	if (errno)
		return (SH_SUCCESS);
	if (ft_strncmp(type_in, "<", 2) == 0)
		fd_in = open(file_in, O_RDONLY, 0644);
	if (fd_in < 0)
		return (SH_ERROR + 1);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	return (SH_SUCCESS);
}

int	redirect_in(char **file_in, char **type_in)
{
	int		i;
	int		status;
	char	*error_file;

	if (!file_in || !type_in)
		return (SH_SUCCESS);
	i = 0;
	error_file = NULL;
	while (file_in[i] && type_in[i])
	{
		status = handle_in_file(file_in[i], type_in[i]);
		if (status == SH_ERROR)
			return (SH_ERROR);
		if (status == SH_ERROR + 1)
			error_file = file_in[i];
		i++;
	}
	if (errno)
		ft_perror("mishelle", error_file);
	return (errno);
}

int	redirect_out(char **file_out, char **type_out)
{
	int	i;
	int	fd_out;

	if (!file_out || !type_out)
		return (SH_SUCCESS);
	i = -1;
	while (file_out[++i])
	{
		fd_out = -1;
		if (type_out[i] && ft_strncmp(type_out[i], ">>", 3) == 0)
			fd_out = open(file_out[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (type_out[i] && ft_strncmp(type_out[i], ">", 2) == 0)
			fd_out = open(file_out[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
		{
			ft_perror("mishelle", file_out[i]);
			break ;
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	return (errno);
}

int	redirect_streams(t_rinity *cmd_struct)
{
	int	status_code;

	status_code = redirect_in(cmd_struct->file_in, cmd_struct->type_in);
	if (status_code)
		return (status_code);
	return (redirect_out(cmd_struct->file_out, cmd_struct->type_out));
}
