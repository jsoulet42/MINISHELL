/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:09:47 by mdiamant          #+#    #+#             */
/*   Updated: 2023/07/12 10:42:53 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/*t_par **init_parsing(char *argv)
{
	t_par	**parsing;
	int		i;

	i = 0;
	if (!parsing)
		return (NULL); //appeler la fonction qui gere les erreurs
	parsing[argv] = NULL;
	return (par);
}*/
int calcSizeType(char *str);
int calcType(char *str);
void	sparse(t_par **p, char *argv);



void	ft_parsing(char *argv)
{
	int		res;
	char	*line;
	char 	*linetmp;
	t_par	**p;

	linetmp = ft_strtrim(argv, " ");
	line = ft_strjoin(linetmp, "\n");
	free(linetmp);
	res = count_arg(line);
	p = malloc(sizeof(t_par *) * (res + 2));
	sparse(p, line);
	free(line);
	printf("il y a %d mots\n", res);
}

void	sparse(t_par **p, char *argv)
{
	int	i;
	int size;

	i = 0;
	while(argv[i])
	{
		i += getSkipCount(argv + i);
		p[i] = malloc(sizeof(t_par));
		p[i]->type = calcType(argv + i);
		size = calcSizeType(argv + i);
		p[i]->str = ft_substr(argv, i, size);
		printf("type : %d, size : %d, str : %s\n\n", p[i]->type, size, p[i]->str);
		i += size;
	}
}

int calcType(char *str)
{
	if (ft_isalnum(str[0]))
		return (1);
	if (is_operand(str))
		return (3);
	if (str[0] == '\'')
		return (4);
	if (str[0] == '\"')
		return (4);

	printf("charatere non reconnu : %s\n", str);
	error_exit("fonction : calcType\n");
	return (0);

}
int calcSizeType(char *str)
{
	int i;

	i = 0;
	if (is_operand(str))
		return (is_operand(str));
	if (simple_quote(str))
		return (simple_quote(str));
	if (double_quote(str))
		return (double_quote(str));
	if (ft_isalnum(str[0]))
	{
		while (str[i])
		{
			if (is_operand(str + i) || simple_quote(str + i)
			|| double_quote(str + i) || str[i] == ' ' || str[i] == '\t')
				break;
			i++;
		}
		return (i);
	}
	return (0);
}

int count_arg(const char *argv)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 1;
	while (argv[i])
	{
		if (argv[i] == ' ')
		{
			i += getSkipCount(argv + i);
			if (is_operand(argv + i) == 0)
				count++;
		}
		j = is_operand(argv + i);
		if (j != 0)
		{
			if (i == 0)
				count--;
			count++;
			i = i + j - 1;
			if (argv[i + 1] != ' ' && argv[i + 1] != '\n')
				count++;
		}
		i++;
	}
	return (count);
}

int	is_operand(const char *str)
{
	int res;
	int i;

	res = 0;
	if (ft_strchr(OPERANDS, *str) != NULL && *str != ' ')
	{
		if (str[0] == str[1])
		{
			res = 2;
			i = 2;
		}
		else
		{
			i = 1;
			res = 1;
		}
		i += getSkipCount(str + i);
		if (is_operand(str + i) != 0)
			error_exit("Robin, sort de ce corps !");
	}
	return (res);
}

int	getSkipCount(const char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}
