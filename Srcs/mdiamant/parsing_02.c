#include "../../Includes/minishell.h"

void	fusion_arg(char **line)
{
	int i;

	i = 1;
	easy_quote_utils(line);
	while (i != 0)
	{
		i = 0;
		i += easy_quote(line);
		i += hard_quote_01(line);
		i += hard_quote_02(line);
	}
}

int	hard_quote_01(char **line)
{
	int	i;
	int	res;
	int	start;

	i = 0;
	res = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '\"' && i > 1 && ft_is_whitespace((*line)[i - 1]) != 0)
		{
			start = i - 1;
			ft_supprchar(line, i);
			while (start >= 0 && ft_is_whitespace((*line)[start]) != 0)
				start--;
			ft_addchar(line, start, "\"");
			while ((*line)[i] && (*line)[i] != '\"')
				i++;
			res = 1;
		}
		else if ((*line)[i] == '\"' && ft_is_whitespace((*line)[i - 1]) == 0)
		{
			i++;
			while ((*line)[i] && (*line)[i] != '\"')
				i++;
		}
		i++;
	}
	return (res);
}

int	hard_quote_02(char **line)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while ((*line)[i])
	{
		if((*line)[i] == '\'')
			i += is_quote(*line + i) + 1;
		if ((*line)[i] == '\"')
		{
			i += is_quote(*line + i) + 1;
			if (ft_is_whitespace((*line)[i + 1]) != 0)
			{
				ft_supprchar(line, i);
				while ((*line)[i] && ft_is_whitespace((*line)[i]) != 0)
					i++;
				ft_addchar(line, i, "\"");
				res = 1;
			}
		}
		i++;
	}
	return (res);
}

int	easy_quote(char **line)
{
	int		i;
	int		res;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '\"' && (*line)[i + 1] == '\"')
		{
			ft_supprchar(line, i);
			ft_supprchar(line, i);
			i -=2;
			res = 1;
		}
		i++;
	}
	return (res);
}

void	easy_quote_utils(char **line)
{
	int		i;
	int		tmp;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '\"')
			i += is_quote_zero(*line + i) + 1;
		if ((*line)[i] == '\'')
		{
			tmp = i;
			i += is_quote_zero(*line + i);
			(*line)[tmp] = '\"';
			(*line)[i] = '\"';
		}
		i++;
	}
}

void	ft_supprchar(char **str, int i)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_substr(*str, 0, i);
	tmp2 = ft_substr(*str, i + 1, ft_strlen(*str));
	free(*str);
	*str = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
}

void	ft_addchar(char **str, int i, char *c)
{
	char	*tmp1;
	char	*tmp2;

	tmp2 = ft_substr(*str, 0, i + 1);
	tmp1 = ft_strjoin_plus(tmp2, c);
	free(tmp2);
	tmp2 = ft_substr(*str, i + ft_strlen(c), ft_strlen(*str));
	free(*str);
		*str = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
}
