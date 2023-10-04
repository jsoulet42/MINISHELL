/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:41:47 by hnogared          #+#    #+#             */
/*   Updated: 2023/09/21 15:35:01 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static int	get_cmd_path(char **to_set, char **bin_paths, char *cmd)
{
	char	*tmp;

	if (cmd[0] == '.' || cmd[0] == '/')
	{
		if (access(cmd, F_OK | X_OK) != 0)
			return (SH_ERROR);
		*to_set = ft_strdup(cmd);
		return (SH_SUCCESS);
	}
	while (*bin_paths)
	{
		tmp = ft_strjoin(*bin_paths++, "/");
		if (!tmp)
			return (SH_ERROR);
		*to_set = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!*to_set)
			return (SH_ERROR);
		if (access(*to_set, F_OK | X_OK) == 0)
			return (SH_SUCCESS);
		free(*to_set);
		*to_set = NULL;
	}
	return (SH_ERROR + 1);
}

char	*get_path(char *cmd, t_env *env)
{
	int		status;
	char	*cmd_path;
	char	**bin_paths;

	g_shell_data.exit_code = 0;
	bin_paths = ft_split(ft_getenv(env, "PATH"), ':');
	cmd_path = NULL;
	if (bin_paths)
	{
		status = get_cmd_path(&cmd_path, bin_paths, cmd);
		free_str_tab((void **)bin_paths);
		if (errno == 13)
			g_shell_data.exit_code = 126;
		else
			g_shell_data.exit_code = errno;
		if (status == SH_ERROR)
			ft_perror("mishelle", cmd);
	}
	if (!bin_paths || status == SH_ERROR + 1)
	{
		ft_fprintf(2, "mishelle: %s: command not found\n", cmd);
		g_shell_data.exit_code = 127;
	}
	errno = 0;
	return (cmd_path);
}
