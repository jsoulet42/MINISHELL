/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils_03.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:14:12 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/07 17:40:01 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

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
}
