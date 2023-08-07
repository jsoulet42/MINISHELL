#include "../../Includes/minishell.h"

int	ft_pwd(int argc, char **argv)
{
	(void)argc;
	(void)argv;
    char buffer[512];

    if (getcwd(buffer, sizeof(buffer)) != NULL)
        printf("Le répertoire de travail actuel est : %s\n", buffer);
	else
	{
        perror("Erreur lors de l'appel à getcwd");
        return (1);
    }
	return (0);
}
