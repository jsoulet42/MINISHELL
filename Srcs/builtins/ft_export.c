/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 03:10:11 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/18 15:58:29 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/hnogared.h"

static void	put_export_error(char *arg)
{
	ft_fprintf(STDERR_FILENO,
		"mishelle: export: `%s': not a valid identifier\n", arg);
}

static int	check_arg(char *arg)
{
	int	i;

	if (!arg)
		return (-2);
	i = 0;
	if (!i && ft_isdigit(arg[i]))
		return (put_export_error(arg), -1);
	while (arg[i] && arg[i] != '+' && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]))
			return (put_export_error(arg), -1);
		i++;
	}
	if (!i)
		return (put_export_error(arg), -1);
	if (arg[i] == '+' && arg[i + 1] == '=')
		return (SH_ADDBACK);
	return (SH_OVERWRITE);
}

int	find_var(t_env **var, char *arg, t_env *env, int mode)
{
	char	*var_name;
	void	*temp;

	if (mode == SH_OVERWRITE)
		temp = ft_strchr(arg, '='); 
	else
		temp = ft_strchr(arg, '+'); 
	if (temp)
		var_name = ft_substr(arg, 0, (char *) temp - arg);
	else
		var_name = ft_strdup(arg);
	if (!var_name)
		return (SH_ERROR);
	*var = get_env_var(env, var_name);
	free(var_name);
	if (*var && !temp)
		return (SH_SUCCESS);
	return (-1);
}

int	export_var(char *arg, t_env *env, int mode)
{
	int		res;
	t_env	*var;
	char	*arg_dup;
	void	*temp;

	res = find_var(&var, arg, env, mode);
	if (res != -1)
		return (res);
	temp = ft_strchr(arg, '=');
	if (!var)
	{
		arg_dup = ft_strdup(arg);
		if (!arg_dup)
			return (SH_ERROR);
		if (mode == SH_ADDBACK && temp)
			ft_memmove(arg_dup + 1, arg_dup, (char *) temp - arg - 1);
		var = new_env_var(arg_dup + (mode == SH_ADDBACK && temp), NULL);
		free(arg_dup);
		if (!var)
			return (SH_ERROR);
		return (env_add_back(&env, var), SH_SUCCESS);
	}
	if (temp)
		update_env_var(var, arg + ((char *) temp - arg + 1), mode);
	return (SH_SUCCESS);
}

int	ft_export(char **argv, t_env *env)
{
	int		mode;

	if (!argv || !*argv)
		return (SH_ERROR);
	if (!argv[1])
		return (print_env(env, SH_ORDERED), SH_SUCCESS);
	while (*(++argv))
	{
		mode = check_arg(*argv);
		if (mode == -2)
			return (1);
		if (mode < 0)
			continue ;
		if (export_var(*argv, env, mode) == SH_ERROR)
			return (SH_ERROR);
	}
	return (SH_SUCCESS);
}
