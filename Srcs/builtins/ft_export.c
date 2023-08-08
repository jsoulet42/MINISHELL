/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:10:28 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/08 11:58:43 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/* Function to put the current argument's error message on the standard error
 *
 * @parent_function check_arg
 * @param char *arg	-> pointer to the current invalid argument (NAME[+/=][VALUE])
 */
static void	put_export_error(char *arg)
{
	ft_fprintf(STDERR_FILENO,
		"mishelle: export: `%s': not a valid identifier\n", arg);
}

/* Function to check if the current argument is valid. If in this case, return
 * if it is an argument for variable value overwriting or appending
 * mode(SH_OVERWRITE)	-> overwrite the variable's value with the new one
 * mode(SH_ADDBAKC)		-> append the new value to the current variable's value
 *
 * @parent_function ft_export
 * @child_function put_export_error
 * @param char *arg	-> pointer to the argument to check (NAME[+/=][VALUE])
 * @return int		-> variable modification mode (SH_OVERWRITE/SH_ADDBACK)
 */
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

/* Function to find + set the environment variable corresponding to the argument
 * mode(SH_OVERWRITE)	-> overwrite the variable's value with the new one
 * mode(SH_ADDBAKC)		-> append the new value to the current variable's value
 *
 * @parent_function export_var
 * @param t_env **var	-> pointer to the variable structure to set
 * @param char *arg		-> pointer to the input argument (NAME[+/=][VALUE])
 * @param t_env *env	-> pointer to the shell environment list to search into
 * @param int mode		-> variable modification mode (SH_OVERWRITE/SH_ADDBACK)
 * @return int			-> function exit code
 */
static int	find_var(t_env **var, char *arg, t_env *env, int mode)
{
	char	*var_name;
	void	*temp;

	if (var)
		*var = NULL;
	if (!var || !arg)
		return (SH_ERROR);
	temp = ft_strchr(arg, '=' * (mode == SH_OVERWRITE)
			+ '+' * (mode != SH_OVERWRITE));
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

/* Function to export/modify an environment variable following an argument
 * mode(SH_OVERWRITE)	-> overwrite the variable's value with the new one
 * mode(SH_ADDBAKC)		-> append the new value to the current variable's value
 *
 * @parent_function ft_export
 * @child_function find_var
 * @param char *arg		-> pointer to the input argument (NAME[+/=][VALUE])
 * @param t_env *env	-> pointer to the shell environment list to modify
 * @param int mode		-> variable modification mode (SH_OVERWRITE/SH_ADDBACK)
 * @return int			-> function exit code
 */
static int	export_var(char *arg, t_env **env, int mode)
{
	int		res;
	t_env	*var;
	char	*arg_dup;
	void	*temp;

	res = find_var(&var, arg, *env, mode);
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
		var = new_env_var(arg_dup + (mode == SH_ADDBACK && temp), NULL, NULL);
		free(arg_dup);
		if (!var)
			return (SH_ERROR);
		return (env_add_back(env, var), SH_SUCCESS);
	}
	if (temp)
		update_env_var(var, arg + ((char *) temp - arg + 1), mode);
	return (SH_SUCCESS);
}

/* Function to modify/add shell environment variables according to arguments
 * Put error for each invalid argument
 *
 * @child_function check_arg
 * @child_function export_var
 * @param char **argv	-> pointer to the input arguments array
 * @param t_env *env	-> pointer to the shell environment to modify
 * @return int			-> function exit code
 */
int	ft_export(char **argv, t_env **env)
{
	int		mode;
	char	*expanded;

	if (!argv || !*argv)
		return (SH_ERROR);
	if (argv[2])
		return (1);
	while (*(++argv))
	{
		expanded = expand_dollars(*argv, *env);
		if (!expanded)
			return (SH_ERROR);
		mode = check_arg(expanded);
		if (mode == -2)
			return (free(expanded), SH_ERROR);
		if (mode > -1 && export_var(expanded, env, mode) == SH_ERROR)
			return (free(expanded), SH_ERROR);
		free(expanded);
	}
	return (SH_SUCCESS);
}
