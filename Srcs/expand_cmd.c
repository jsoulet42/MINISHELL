/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:57:49 by hnogared          #+#    #+#             */
/*   Updated: 2023/08/27 16:27:07 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	check_quotes(char *str)
{
	char	quote;

	if (!str)
		return (1);
	quote = 0;
	while (*str)
	{
		if ((*str == '\'' || *str == '"') && (quote == 0 || quote == *str))
			quote = (quote == 0) * *str;
		str++;
	}
	return (quote != 0);
}

static char	**expand_cmd_parts(char **cmd_tab, t_env *env)
{
	int		trigger;
	char	*temp;
	char	**res;

	if (!cmd_tab || !env)
		return (NULL);
	res = cmd_tab;
	trigger = 0;
	cmd_tab--;
	while (*(++cmd_tab))
	{
		if (!trigger && *cmd_tab[0] == '\'')
		{
			ft_supprchar(cmd_tab, 0);
			ft_supprchar(cmd_tab + 1, 0);
			continue ;
		}
		if ((count_chars(*cmd_tab, '"') % 2) != 0)
			trigger = (trigger == 0);
		if (!ft_strchr(*cmd_tab, '$'))
			continue ;
		temp = expand_dollars(*cmd_tab, env);
		if (!temp)
			return (NULL);
		free(*cmd_tab);
		*cmd_tab = temp;
	}
	return (res);
}

// TODO mode for '' and "" included or not (see bash heredoc)

char	*expand_cmd(char *cmd, t_env *env)
{
	char	*res;
	char	**quotes_split;

	if (!cmd | !env)
		return (NULL);
//	if (check_quotes(cmd))
//		return (NULL);
	quotes_split = ft_keep_split(cmd, '\'');
	if (!quotes_split)
		return (NULL);
	if (!expand_cmd_parts(quotes_split, env))
		return (free_str_tab((void **)quotes_split), NULL);
	res = join_str_tab((const char **)quotes_split);
	free_str_tab((void **)quotes_split);
	ft_printf("%s\n", res);
	return (res);
}
