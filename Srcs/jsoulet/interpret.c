/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:30:07 by jsoulet           #+#    #+#             */
/*   Updated: 2023/07/14 17:15:56 by hnogared         ###   ########.fr       */
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
	len = 1;
	while (par[i])
	{
		if (par[i]->type == 1)
			len++;
		i++;
	}
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

	j = 0;
	i = 0;
	commande = malloc(sizeof(char *) * commande_len(par) + 1);
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


void execute_cmd(t_par *par, t_env *env)
{
	char **commande;
	char *path;

	commande = create_commande(par);
	if (commande == NULL)
		return ;
	path = get_path(commande[0], env);
	if (!path)
		printf("minishell: command not found: %s\n", commande[0]);
	else
		execve(path, commande, env);
	free_str_tab(commande);
}

char *get_path(char *cmd, t_env *env)
{
	int i;
	char **path;
	char *path_cmd;

	i = 0;
	while (env)
	{
		if (ft_strncmp(env->name, "PATH", 4) == 0)
		{
			path = ft_split(env->value, ':');
			path_cmd = get_path_cmd(path, cmd);
			free_str_tab(path);
			return (path_cmd);
		}
		env = env->next;
	}
	return (NULL);
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
			dup2(fd[1], 1);
			close(fd[0]);
			execute_cmd(par[i], env);
		}
		else
		{
			dup2(fd[0], 0);
			close(fd[1]);
			waitpid(pid, NULL, 0);
		}
		i++;
	}
}

