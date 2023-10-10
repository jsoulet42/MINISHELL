/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:41:47 by hnogared          #+#    #+#             */
/*   Updated: 2023/10/05 15:21:41 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	get_cmd_path(char **to_set, char *cmd, char *path)
{
	int		i;
	char	*tmp;
	char	**bin_paths;

	if (ft_strchr(cmd, '/'))
	{
		*to_set = ft_strdup(
				(void *)((uintptr_t)cmd * !access(cmd, F_OK | X_OK)));
		return ;
	}
	bin_paths = ft_split(path, ':');
	if (!bin_paths)
		return ;
	i = 0;
	while (bin_paths[i])
	{
		tmp = ft_strjoin(bin_paths[i++], "/");
		*to_set = ft_strjoin(tmp, cmd);
		safe_free((void **) &tmp);
		if (!*to_set || !access(*to_set, F_OK | X_OK))
			break ;
		safe_free((void **) to_set);
	}
	free_str_tab((void **) bin_paths);
	return ;
}

char	*get_path(char *cmd, t_env *env)
{
	char	*path;
	char	*cmd_path;

	cmd_path = NULL;
	path = ft_getenv(env, "PATH");
	if (!path)
		errno = 2;
	get_cmd_path(&cmd_path, cmd, path);
	if (cmd_path)
	{
		errno = 0;
		return (cmd_path);
	}
	g_shell_data.exit_code = 126 * (errno == 13) + errno * (errno != 13);
	if (g_shell_data.exit_code != 2)
		ft_perror("mishelle", cmd);
	else
	{
		ft_fprintf(2, "mishelle: %s: command not found\n", cmd);
		g_shell_data.exit_code = 127;
	}
	errno = 0;
	return (NULL);
}
