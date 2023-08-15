/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils_03.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:14:12 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/14 21:01:38 by hnogared         ###   ########.fr       */
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

/* Function to display an environment's linked list of variables on terminal
 * following a given mode
 * mode(SH_DISORDERED)	-> display only the variables with a value disorderly
 * mode(SH_ORDERED)		-> display all variables in alphabetical order
 *
 * @param t_env *env_list	-> pointer to the environment to display
 * @param int mode			-> display mode of the environment
 */
void	print_env(t_env *env_list, int mode)
{
	char	*check;
	char	**temp;
	char	**str_env;

	if (mode == SH_ORDERED)
	{
		str_env = order_str_tab(env_to_str_tab(&env_list), '=');
		if (!str_env)
			return ;
		temp = str_env;
		while (*temp)
		{
			check = ft_strchr(*temp, '=');
			mode = '"' * (check && !*(check + 1));
			if ((*temp)[0] != '_' || ((*temp)[1] && (*temp)[1] != '='))
				printf("declare -x %s%c%c\n", *temp, mode, mode);
			temp++;
		}
		return (free_str_tab((void **) str_env));
	}
	while (env_list)
	{
		printf("%s\n", env_list->display);
		env_list = env_list->next;
	}
}
