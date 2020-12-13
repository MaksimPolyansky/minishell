#include "parser.h"

void	search_cmd(t_parser *tuk, char *line)
{
	int		i;

	i = tuk->i;
	while (line[tuk->i] && line[tuk->i] != ' ')
		tuk->i++;
	tuk->cmd = ft_substr(line, i, tuk->i - i);
}

void	search_flag(t_parser *tuk, char *line)
{
	int		i;

	i = tuk->i;
	while (line[tuk->i] && line[tuk->i] != ' ')
		tuk->i++;
	tuk->flag = ft_substr(line, i, tuk->i - i);
}

void	search_arg(t_parser *tuk, char *line)
{
	int		i;

	i = tuk->i;
	while (line[tuk->i] && line[tuk->i] != ' ')
		tuk->i++;
	tuk->arg[tuk->i_arg] = ft_substr(line, i, tuk->i - i);
	tuk->i_arg++;
}

t_parser	*parser_malloc(void)
{
	t_parser	*tuk;

	if (!(tuk = (t_parser*)ft_calloc(sizeof(t_parser), 1)))
		return (NULL);
	tuk->i = -1;
	if (!(tuk->arg = (char**)malloc(sizeof(char*))))
		return (NULL);
	return (tuk);
}

t_parser	*parser(char *line)
{
	t_parser	*tuk;

	if (!(tuk = parser_malloc()))
		return (NULL);
	while (line[++tuk->i])
	{
		if (!tuk->cmd && line[tuk->i] != ' ')
			search_cmd(tuk, line);
		else if (tuk->cmd && line[tuk->i] == '-')
			search_flag(tuk, line);
		else if (tuk->cmd && line[tuk->i] != ' ')
			search_arg(tuk, line);
	//	else if (line[tuk->i] == '|')
	//	else if (line[tuk->i] == ';')
	//	else if (line[tuk->i] == '<' && line[tuk->i] == '>' && line[tuk->i] == '>>')
		else if (line[tuk->i] == ' ')
			tuk->i++;
		else
			return (NULL);
	}
	return (tuk);
}
