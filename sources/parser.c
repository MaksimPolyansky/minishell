#include "parser.h"

int				parser_next(t_tokenizer *token, t_parser *tuk)
{
	if (token->sort_tokens[tuk->i][0] == 59 && token->sort_tokens[tuk->i][1] == '\0')
	{
		tuk->i++;
		tuk->sem = parser(token);
		return (1);
	}
	else if (token->sort_tokens[tuk->i][0] == '|' && token->sort_tokens[tuk->i][1] == '\0')
	{
		tuk->i++;
		tuk->pipe = parser(token);
		return (1);
	}
	else if ((token->sort_tokens[tuk->i][0] == 60 && token->sort_tokens[tuk->i][1] == '\0') \
	|| (token->sort_tokens[tuk->i][0] == 62 && token->sort_tokens[tuk->i][1] == '\0'))
	{
		tuk->i++;
		tuk->redir = parser(token);
		return (1);
	}
	return (0);
}

t_parser		*parser(t_tokenizer *token)
{
	t_parser	*tuk;

	if (!(tuk = (t_parser*)ft_calloc(sizeof(t_parser), 1)) \
	|| !(tuk->arg = (char**)ft_calloc(sizeof(char*), (tuk->malloc_arg = token->i))))
		exit(EXIT_FAILURE);
	while (token->sort_tokens[tuk->i])
	{
		if (parser_next(token, tuk))
			;
		else if (!tuk->cmd)
			tuk->cmd = ft_strdup(token->sort_tokens[tuk->i++]);
		else if (tuk->cmd)
			tuk->arg[tuk->i_arg++] = ft_strdup(token->sort_tokens[tuk->i++]);
	}
	return (tuk);
}
