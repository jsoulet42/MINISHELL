/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:30:07 by jsoulet           #+#    #+#             */
/*   Updated: 2023/07/17 09:57:01 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/*si il y a plusieur operateur de suite on print une erreur
	et on return le print de l'erreur*/
int check_line(t_par **par)
{
	int	i;

	i = 0;
	while (par[i])
	{
		if (par[i]->type != 0 && par[i + 1] && par[i + 1]->type != 0)
		{
			printf("minishell: syntax error bad operand `");
			return(printf("%s'\n", par[i + 1]->str));
		}
		if (par[i]->type != 0 && par[i + 1] == NULL)
		{
			printf("minishell: syntax error bad operand `");
			return(printf("%s'\n", par[i]->str));
		}
		i++;
	}
	return (0);
}

int commande_len(t_par **par)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (par[i] && par[i]->type == 1)
		i++;
	while (par[i + len] && par[i + len]->type != 1)
		len++;
	return (len);
}


/* on met dans un char **la prochaine commande a execve
	 et si cette fonction return NULL c'est qu'il n'y a plus de commande
		et donc que le programme doit s'arreter */
char **create_commande(t_par **par)
{
	int		j;
	int		i;
	char	**commande;

	if (!par)
		return (NULL);
	j = 0;
	i = 0;
	commande = (char **) malloc(sizeof(char *) * (commande_len(par) + 1));
	while (par[i] && par[i]->type == 1)
		i++;
	if (par[i] == NULL)
		return (NULL);
	while (par[i] && par[i]->type != 1)
	{
		commande[j] = par[i]->str;
		par[i]->type = 1;
		j++;
		i++;
	}
	commande[j] = NULL;
	return (commande);
}


void execute_cmd(t_par **par, t_env *env)
{
	char **commande;
	char *path;

	commande = create_commande(par);
	if (commande == NULL)
		return ;
	path = get_path(commande[0], env);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(commande[0], 2);
		ft_putstr_fd("\n", 2);
	}
	else
		execve(path, commande, env_to_str_tab(env));
	free(commande);
}

char *get_path(char *cmd, t_env *env)
{
	char	*var;
	char **path;
	char *path_cmd;

	var = ft_getenv(env, "PATH");
	if (!var)
		return (NULL);
	path = ft_split(var, ':');
	path_cmd = get_path_cmd(path, cmd);
	free_str_tab(path);
	return (path_cmd);
}

char *get_path_cmd(char **path, char *cmd)
{
	int		i;
	char	*path_cmd;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			return (NULL);
		path_cmd = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!path_cmd)
			return (NULL);
		if (access(path_cmd, F_OK) == 0)
			return (path_cmd);
		free(path_cmd);
		i++;
	}
	return (NULL);
}

void	piper(t_par **par, t_env *env)
{
	int		fd[2];
	int		i;
	pid_t	pid;

	i = 0;
	while (par[i])
	{
		if (pipe(fd) == -1)
			return ;
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			close(fd[0]);
			dup2(fd[1], 1);
			execute_cmd(par, env);
		}
		else
		{
			waitpid(pid, &g_shell_data->in, 0);
			close(fd[1]);
			dup2(fd[0], 0);
		}
		i++;
	}
}

