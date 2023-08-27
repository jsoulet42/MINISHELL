/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 23:02:53 by hnogared          #+#    #+#             */
/*   Updated: 2023/08/27 01:55:51 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static char	*start_expand_dollar(char *str, t_env *env)
{
	int		i;
	char	*temp;
	char	*res;
	char	*var_name;

	if (!str || !env)
		return (NULL);
	if (str[1] == '?')
	{
		temp = str + 2;
		res = ft_itoa(g_shell_data->exit_code);
		ft_free_strcat(&res, temp, 0, ft_strlen(temp));
		return (res);
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

char	*expand_dollars(char *str, t_env *env)
{
	int		i;
	char	*res;
	char	*temp;
	char	**dollar_split;

	dollar_split = ft_keep_split(str, '$');
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
/*
int	get_dollar_value(char **to_set, char *to_search, t_env *env)
{
	int		i;
	char	*var_name;

	if (!to_search || !env)
		return (0);
	i = 1;
	if (to_search[i] == '?')
	{
		*to_set = ft_itoa(g_shell_data->exit_code);
		return (2);
	}
	while (to_search[i] && ft_isalnum(to_search[i]))
		i++;
	var_name = ft_substr(to_search, 1, i - 1);
	*to_set = ft_getenv(env, var_name);
	if (var_name)
		free(var_name);
	return (i);
}

struct s_doll
{
	int		id[3];
	char	*res;
	char	*temp;
};

char	*expand_dollars(char *s, t_env *env)
{
	struct s_doll	d;

	if (!s || !env)
		return (ft_strdup(s));
	d = init_doll();
	while (s[++d.id[0]])
	{
		if (s[d.id[0]] == '\"')
			d.id[2]++;
		if (s[d.id[0]] == '\'' && !(d.id[2] % 2))
			d.id[0] += is_quote_zero(s + d.id[0]);
		if (s[d.id[0]] != '$')
			continue ;
		if (d.id[0] != d.id[1] && !ft_free_strcat(&d.res, s, d.id[1], d.id[0]))
			return (NULL);
		d.id[1] = d.id[0];
		d.id[1] += get_dollar_value(&d.temp, s + d.id[0], env);
		if (d.temp && !ft_free_strcat(&d.res, d.temp, 0, ft_strlen(d.temp)))
			return (NULL);
		d.id[0] = d.id[1] - 1;
	}
	if ((!d.res || d.id[0] != d.id[1])
		&& !ft_free_strcat(&d.res, s, d.id[1], d.id[0]))
		return (NULL);
	return (d.res);
}

struct s_doll	init_doll(void)
{
	struct s_doll	doll;

	doll.id[0] = -1;
	doll.id[1] = 0;
	doll.id[2] = 0;
	doll.res = NULL;
	return (doll);
}*/
