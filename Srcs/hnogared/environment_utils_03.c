#include "../../Includes/hnogared.h"

int	get_dollar_value(char **to_set, char *to_search, t_env *env)
{
	int		i;
	char	*var_name;

	if (!to_search || !env)
		return (0);
	i = 1;
	while (to_search[i] && ft_isalnum(to_search[i]))
		i++;
	var_name = ft_substr(to_search, 1, i - 1);
	*to_set = ft_getenv(env, var_name);
	if (var_name)
		free(var_name);
	return (i);
}
char	*expand_dollars(char *str, t_env *env)
{
	int		id[3];
	char	*res;
	char	*temp;

	if (!str || !env)
		return (ft_strdup(str));
	res = NULL;
	id[0] = -1;
	id[1] = 0;
	id[2] = 0;
	while (str[++id[0]])
	{
		if (str[id[0]] == '\"')
			id[2]++;
		if(str[id[0]] == '\'' && !(id[2] % 2))
			id[0] += is_quote_zero(str + id[0]);
		if (str[id[0]] != '$')
			continue ;
		if (id[0] != id[1] && !ft_free_strcat(&res, str, id[1], id[0]))
			return (NULL);
		id[1] = id[0];
		id[1] += get_dollar_value(&temp, str + id[0], env);
		if (temp && !ft_free_strcat(&res, temp, 0, ft_strlen(temp)))
			return (NULL);
		id[0] = id[1] - 1;
	}
	if ((!res || id[0] != id[1]) && !ft_free_strcat(&res, str, id[1], id[0]))
		return (NULL);
	return (res);
}
/*
echo $USERNAME $USERNAME

while (line[i])
{
if line[i] = '
i += is_quote(line + i)
if line[i] = $
expende_dollars(line + i)
}

*/
