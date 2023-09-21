/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 23:02:53 by hnogared          #+#    #+#             */
/*   Updated: 2023/09/21 07:59:48 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static char	*start_expand_dollar(char *str, t_env *env)
{
	int		i;
	char	*temp;
	char	*res;
	char	*var_name;

	if (!str || !env)
		return (NULL);
	if (str[0] && str[1] == '?')
	{
		res = ft_itoa(g_shell_data.exit_code);
		temp = ft_strjoin_plus(res, str + 2);
		safe_free((void **) &res);
		return (temp);
	}
	i = 1;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	temp = str + i;
	var_name = ft_substr(str, 1, i - 1);
	if (!var_name)
		return (NULL);
	res = ft_getenv(env, var_name);
	safe_free((void **)&var_name);
	return (ft_strjoin_plus(res, temp));
}

static int	dollar_word_len(char *str)
{
	char	*moved;

	if (!str || !*str)
		return (0);
	moved = str + 1;
	while (*moved && *moved != '$' && !ft_isoperand(*moved)
		&& !ft_is_whitespace(*moved))
		moved++;
	return (moved - str);
}

char	*expand_dollars(char *str, t_env *env)
{
	int		i;
	char	*res;
	char	*temp;
	char	**dollar_split;

	dollar_split = ft_fsplit(str, dollar_word_len);
	if (!dollar_split)
		return (NULL);
	i = -1;
	while (dollar_split[++i])
	{
		if (dollar_split[i][0] != '$' || !dollar_split[i][1])
			continue ;
		temp = start_expand_dollar(dollar_split[i], env);
		if (!temp)
			break ;
		free(dollar_split[i]);
		dollar_split[i] = temp;
	}
	if (!dollar_split[i])
		res = join_str_tab((const char **)dollar_split);
	else
		res = NULL;
	free_str_tab((void **)dollar_split);
	return (res);
}
