#include "../../Includes/minishell.h"

t_rinity	**ft_parsing(char *argv)
{
	char		*line;
	char		*line2;
	t_rinity	**t;

	line2 = ft_strtrim(argv, " ");
	line = expand_dollars(line2, g_shell_data->env);
	free(line2);
	g_shell_data->par = sparse(line);
	print_t_par(g_shell_data->par);
	free(line);
	if (check_line(g_shell_data->par))
		return (NULL);
	t = t_rinity_init(g_shell_data->par);
	if (!t)
		ft_fprintf(2, "malloc error // ft_parsing\n");
	print_t_rinity(t);
	return (t);
}

static t_rinity	*t_rinity_init_utils(t_par **p, int len)
{
	t_rinity	*t;

	t = (t_rinity *) malloc(sizeof(t_rinity));
	if (!t)
		ft_putstr_fd("malloc error // init_t_rinity\n", 2);
	t->cmd = NULL;
	t->type_in = NULL;
	t->type_out = NULL;
	t->file_in = NULL;
	t->file_out = NULL;
	t->kafka = NULL;
	t->cmd = create_commande(p, len);
	t->builtin = agent_smith(t->cmd[0]);
	t->type_in = create_type_in(p, len);
	t->type_out = create_type_out(p, len);
	t->file_in = create_file_in(p, len);
	t->file_out = create_file_out(p, len);
	t->kafka = create_kafka(p, len);
	return (t);
}

t_rinity	**t_rinity_init(t_par **p)
{
	t_rinity	**t;
	int			cmd;
	int			i;
	int			len;

	i = 0;
	len = 0;
	cmd = real_cmd(p);
	t = (t_rinity **) malloc(sizeof(t_rinity *) * (cmd + 1));
	while (i < cmd && p[len])
	{
		t[i] = t_rinity_init_utils(p, len);
		len = next_pipe(p, i);
		i++;
	}
	t[cmd] = NULL;
	return (t);
}
