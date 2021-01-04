#include "parser.h"

void free_parser(t_parser *tuk)
{
	int i;

	if (tuk->cmd)
		free(tuk->cmd);
	i = 0;
	if (tuk->arg)
	{
		while (i < tuk->malloc_arg)
			free(tuk->arg[i++]);
		free(tuk->arg);
	}
	if (tuk->pipe)
		free_parser(tuk->pipe);
	if (tuk->redir)
		free_parser(tuk->redir);
	if (tuk->sem)
		free_parser(tuk->sem);
	if (tuk)
		free(tuk);
}

int parser_next(t_tokenizer *token, t_parser *tuk)
{
	if (token->sort_tokens[token->next][0] == 59 && token->sort_tokens[token->next][1] == '\0')
	{
		token->next++;
		tuk->sem = parser(token);
		return (1);
	}
	else if (token->sort_tokens[token->next][0] == '|' && token->sort_tokens[token->next][1] == '\0')
	{
		token->next++;
		tuk->pipe = parser(token);
		return (1);
	}
	else if ((token->sort_tokens[token->next][0] == 60 || token->sort_tokens[token->next][0] == 62) && token->sort_tokens[token->next][1] == '\0')
	{
		token->next++;
		tuk->redir = parser(token);
		return (1);
	}
	return (0);
}

t_parser *parser(t_tokenizer *token)
{
	t_parser *tuk;

	if (!(tuk = (t_parser *)ft_calloc(sizeof(t_parser), 1)) || !(tuk->arg = (char **)ft_calloc(sizeof(char *), (tuk->malloc_arg = token->i))))
		exit(EXIT_FAILURE);
	tuk->i_arg = 1;
	while (token->sort_tokens[token->next])
	{
		if (parser_next(token, tuk))
			;
		else if (!tuk->cmd)
		{
			if (!(tuk->cmd = ft_strdup(token->sort_tokens[token->next++])))
				exit(EXIT_FAILURE);
		}
		else if (tuk->cmd)
		{
			if (!(tuk->arg[tuk->i_arg++] = ft_strdup(token->sort_tokens[token->next++])))
				exit(EXIT_FAILURE);
		}
	}
	return (tuk);
}
