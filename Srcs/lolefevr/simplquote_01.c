#include "../../Includes/minishell.h"

int	simplquote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((int)str[i] == 39)
			return (i);
		i++;
	}
	return (-1);
}
