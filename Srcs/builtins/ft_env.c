#include "../../Includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	int	i;

	(void)argc;
	(void)argv;
	if (!env)
		return (1);
	i = -1;
	while (env[++i])
	{
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
	}
	return (0);
}
