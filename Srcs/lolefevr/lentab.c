#include "../../Includes/minishell.h"

int	lentab(char **tableau)
{
	int	i;

	i = -1;
	while(tableau[++i])
		i = i;
	return (i);
}
