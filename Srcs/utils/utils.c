/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_03.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:22:11 by hnogared          #+#    #+#             */
/*   Updated: 2023/09/21 08:00:02 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	ft_min(int a, int b)
{
	return ((a <= b) * a + (a > b) * b);
}

int	ft_is_whitespace(char str)
{
	return (!str || (str > 8 && str < 14) || str == 32 || str == 127);
}

int	ft_isoperand(char c)
{
	char	to_find[2];

	to_find[0] = c;
	to_find[1] = 0;
	return (c != ':'
		&& ft_strnstr(OPERANDS, to_find, ft_strlen(OPERANDS)));
}

int	ft_strccmp(const char *str1, const char *str2, char limit)
{
	int	i;

	if (!str1 || !str2)
		return (0);
	i = 0;
	while (str1[i] && str2[i] && str1[i] != limit && str2[i] != limit)
	{
		if (str1[i] != str2[i])
			return ((unsigned char) str1[i] - (unsigned char) str2[i]);
		i++;
	}
	if (str1[i] && str1[i] != limit)
		return ((unsigned char) str1[i]);
	if (str2[i] && str2[i] != limit)
		return (- (unsigned char) str2[i]);
	return (0);
}

char	*ft_strchrnul(const char *str, int c)
{
	char	*temp;

	if (!str)
		return (NULL);
	temp = ft_strchr(str, c);
	if (!temp)
		return (ft_strchr(str, 0));
	return (temp);
}
