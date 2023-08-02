
#include "../../Includes/minishell.h"

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
}
