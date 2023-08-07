#include "../../Includes/minishell.h"

int	doublquote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((int)str[i] == 34)
			return (i);
		i++;
	}
	return (-1);
}
