#include "../../Includes/minishell.h"

int	main(int argc, char **argv)
{
	char buffer[512];

	(void)argc;
	(void)argv;
	if (getcwd(buffer, sizeof(buffer)) != NULL)
		printf("Le répertoire de travail actuel est : %s\n", buffer);
	else
	{
		perror("Erreur lors de l'appel à getcwd");
		return (1);
	}
	return (0);
}
