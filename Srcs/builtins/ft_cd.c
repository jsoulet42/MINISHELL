#include "../../Includes/minishell.h"

int	change_directory(const char *path)
{
	if (chdir(path) == 0)
		return (0);
	else
	{
		perror("Erreur lors du changement de répertoire");
		return (-1);
	}
}

t_env	*update_pwd(char *oldpwd, char *pwd, t_env **env)
{
	t_env	*found;
	t_env	*test;

	found = g_shell_data->env;
	found = get_env_var(found, "PWD");
	found->value = pwd;
	found = get_env_var(found, "OLDPWD");
	found->value = oldpwd;
	test = *env;
	test = get_env_var(test, "PWD");
	return (*env);
}

t_env *ft_cd(int argc ,char **argv, t_env **env)
{
	int		changedir;
	char	*home;
	char	*oldpwd;
	char	*pwd;
	t_env	*envi;
	t_env	*envtest;

	envtest = *env;
	envi = *env;
	oldpwd = malloc(sizeof(char) * 512);
	pwd = malloc(sizeof(char) * 512);
	getcwd(oldpwd, 512);
	home = ft_getenv(envi, "HOME");
	changedir = 42;
	if ((argc < 2 ) || (argv[1][0] == '~'))
	{
		if (home)
			changedir = change_directory(home);
		else
		{
			ft_printf("HOME not set");
			return (*env);
		}
	}
	else
		changedir = change_directory(argv[1]);
	if (changedir == 0)
		printf("Répertoire changé avec succès.\n");
	envtest = update_pwd(oldpwd, getcwd(pwd, 512), env);
	return (envtest);
}
