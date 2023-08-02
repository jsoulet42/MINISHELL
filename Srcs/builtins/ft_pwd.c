
#include "../../Includes/minishell.h"

void	ft_pwd()
{
	char buffer[512];
  if (getcwd(buffer, sizeof(buffer)) != NULL)
    printf("Le répertoire de travail actuel est : %s\n", buffer);
	else
  {
    perror("Erreur lors de l'appel à getcwd");
      return ;
  }
}
