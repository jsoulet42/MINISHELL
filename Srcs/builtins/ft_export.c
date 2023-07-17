/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 03:10:11 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/17 17:46:04 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/hnogared.h"

static void	put_export_error(char *arg)
{
	printf("mishelle: export: `%s': not a valid identifier\n", arg);
}

static int	check_arg(char *arg)
{
	int	i;
	
	if (!arg)
		return (-1);
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '+')
			break ;
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

int	export_var(char *arg, int mode)
{
	int	mode;

	if (mode == SH_OVERWRITE)
		var_name = ft_substr(*argv, 0, ft_strchr(arg, '=') - arg);
	else
		var_name = ft_substr(*argv, 0, ft_strchr(arg, '+') - arg);
	var = get_env_var(env, var_name);
	free(var_name);
	if (!var)
	{
		var = new_env_var(arg, NULL);
		if (!var)
			return (SH_ERROR);
		env_add_back(&env, var);
		return (SH_SUCCESS);
	}
	len = ft_strchr(arg, '=') - arg + 1;
	update_env_var(var, arg + len, mode);
	return (SH_SUCCESS);
}

int	ft_export(char **argv, t_env *env)
{
	int		mode;
	int		len;
	char	*var_name;
	t_env	*var;

	if (!argv || !*argv)
		return (SH_ERROR);
	if (!argv[1])
		return (print_env(env, SH_ORDERED), SH_SUCCESS);
	argv++;
	while (*argv)
	{
		mode = check_arg(*argv);
		if (mode < 0)
			return (1);
		if (export_var(*argv, mode) == SH_ERROR)
			return (SH_ERROR);
		argv++;
	}
	return (SH_SUCCESS);
}
