
#include "../../Includes/minishell.h"
/*
int	ft_env(t_env	*env)
{
	t_env	*temp;
	int	len;
	temp = env;
	while (temp)
	{
		if (temp->name)
			printf("%s", temp->name);
		len = strlen(temp->name);
		if (temp->name[len] != '=')
			printf("=");
		if (temp->value)
			printf("%s\n", temp->value);
		temp = temp->next;
	}
	return (0);
}*/
int	ft_env(int argc, char **argv, char **env)
{
	int	i;

	(void)argc;
	(void)argv;
	if (!env)
		return (1);
	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
	return (0);
}
