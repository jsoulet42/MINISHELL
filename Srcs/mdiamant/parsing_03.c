#include "../../Includes/minishell.h"

static void	print_t_rinity_02(t_rinity **t, int i, int j, int len);

static int	pw(int i, char c)
{
	int	j;

	j = 0;
	if (i < 0)
	{
		j += ft_fprintf(2, "\t|\n");
		return (j);
	}
	while (i--)
		j += ft_fprintf(2, "%c", c);
	j += ft_fprintf(2, "|\n");
	return (j);
}

static int	print_strstr(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str || !str[0])
		return (ft_fprintf(2, "NULL"));
	while (str[i])
	{
		j += ft_fprintf(2, "[%s] ", str[i]);
		i++;
	}
	return (j);
}

void	print_t_rinity(t_rinity **t)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	if (!t)
		return ;
	while (t[i])
	{
		len = ft_fprintf(2, " _________________________");
		len += ft_fprintf(2, "____________________________") - 6;
		ft_fprintf(2, "\n|");
		pw(len + 5, ' ');
		j = ft_fprintf(2, "|\tLa commande est : ");
		j += print_strstr(t[i]->command);
		pw(len - j, ' ');
		j = ft_fprintf(2, "|\ttype_in  : ");
		j += print_strstr(t[i]->type_in);
		pw(len - j, ' ');
		print_t_rinity_02(t, i, j, len);
		i++;
	}
}

static void	print_t_rinity_02(t_rinity **t, int i, int j, int len)
{
	j = ft_fprintf(2, "|\ttype_out : ");
	j += print_strstr(t[i]->type_out);
	pw(len - j, ' ');
	j = ft_fprintf(2, "|\tfile_in  : ");
	j += print_strstr(t[i]->file_in);
	pw(len - j, ' ');
	j = ft_fprintf(2, "|\tfile_out : ");
	j += print_strstr(t[i]->file_out);
	pw(len - j, ' ');
	j = ft_fprintf(2, "|\tkafka    : ");
	j += print_strstr(t[i]->kafka);
	pw(len - j, ' ');
	ft_fprintf(2, "|______________________________");
	ft_fprintf(2, "_______________________|\n\n");
}

void	print_t_par(t_par **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		ft_fprintf(2, "p[%d] :", i);
		ft_fprintf(2, " str : [%s] // ", p[i]->str);
		ft_fprintf(2, "type : [%d] // ", p[i]->type);
		ft_fprintf(2, "fusion : [%d]\n", p[i]->fusion);
		i++;
	}
}
