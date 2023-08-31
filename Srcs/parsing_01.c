/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:21:56 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/31 14:30:44 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

t_rinity	**ft_parsing(char *argv)
{
//	int			res;
	char		**line_tab;
	t_rinity	**t;

//	res = count_arg(argv, 0);
//	g_shell_data->par = (t_par **) malloc(sizeof(t_par *) * (res + 1));
//	if (!g_shell_data->par)
//		return (NULL);
	line_tab = expand_line(argv, g_shell_data->env);
	if (!line_tab)
		return (NULL);
//	sparse(g_shell_data->par, cmd_tab);
//	if (check_line(g_shell_data->par))
//		return (NULL);
	t = t_rinity_init(line_tab);
	free_str_tab((void **)line_tab);
	return (NULL);
	if (!t)
		ft_perror("mishelle", __func__);
	return (t);
}
/*
static char	*ft_unquote(char *str)
{
	char	*temp;

	temp = ft_strtrim(*line_tab, " \t\n\v\f\r");
	if (!temp)
		return (NULL);
	str = temp;
	
	}
*/
static t_rinity	*t_rinity_init_utils(char **line_tab)
{
//	char		*temp;
	t_rinity	*t;

	t = (t_rinity *) ft_calloc(1, sizeof(t_rinity));
	if (!t)
		ft_putstr_fd("malloc error // init_t_rinity\n", 2);
//	t->cmd = create_commande(line_tab, cmd_len);
//	t->builtin = agent_smith(t->cmd[0]);
	while (*line_tab)
	{
//		temp = ft_unquote(*line_tab, " \t\n\v\f\r");
//		if (!temp)
//			return (NULL);
		t->type_in = create_type_in(line_tab);
		t->type_out = create_type_out(line_tab);
		t->file_in = create_file_in(line_tab);
		t->file_out = create_file_out(line_tab);
		t->kafka = create_kafka(line_tab);
	}
	print_str_tab(*char[]{"hey", "qwdqwd", NULL});
	return (t);
}

t_rinity	**t_rinity_init(char **line_tab)
{
	int			cmds_count;
	t_rinity	**t;
	t_rinity	**temp;

	cmds_count = real_cmd(line_tab);
	t = (t_rinity **) ft_calloc(sizeof(t_rinity *), cmds_count + 1);
	if (!t)
		return (NULL);
	temp = t;
	while (cmds_count--)
	{
		*temp = t_rinity_init_utils(line_tab);
		if (!*temp)
			return(free_trinity(t), NULL);
		line_tab += next_pipe(line_tab) + 1;
		temp++;
	}
	temp = NULL;
	return (t);
}

void	ft_supprchar(char **str, int i)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_substr(*str, 0, i);
	tmp2 = ft_substr(*str, i + 1, ft_strlen(*str));
	free(*str);
	*str = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
}
