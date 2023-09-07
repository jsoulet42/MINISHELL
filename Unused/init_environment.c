/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:40:55 by hnogared          #+#    #+#             */
/*   Updated: 2023/09/07 14:40:57 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_pwd2(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	return (pwd);
}

char	*modif_pwd2(void)
{
	char	*pwd;
	char	*tmp_pwd;

	pwd = ft_pwd2();
	if (!pwd)
		return (NULL);
	tmp_pwd = ft_strjoin("OLDPWD=", pwd);
	free(pwd);
	pwd = NULL;
	if (!tmp_pwd)
		return (NULL);
	return (tmp_pwd);
}
