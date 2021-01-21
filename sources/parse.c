#include "parse.h"

int		free_line(char *line)
{
	if (line)
		free(line);
	line = NULL;
	return (0);
}

int		free_dline(char **line)
{
	int		i;

	if (line)
	{
		i = 0;
		while (line[i])
		{
			free(line[i]);
			line[i++] = NULL;
		}
		line[i] = NULL;
		free(line);
	}
	line = NULL;
	return (0);
}

void	free_tokens(t_tokenizer *tokens)
{
	tokens->line = NULL;
	free_dline(tokens->tokens);
}

void	parse_clear(t_parser *parse)
{
	parse->arg = NULL;
	parse->cmd = NULL;
	parse->i_arg = 0;
	parse->pipe = NULL;
	parse->redir = NULL;
	parse->type = 0;
}

void	free_parse(t_parser *parse)
{
	if (parse->cmd)
		free(parse->cmd);
	parse->cmd = NULL;
	if (parse->ard_red)
		free(parse->ard_red);
	parse->ard_red = NULL;
	free_dline(parse->arg);
	if (parse->pipe)
		free_parse(parse->pipe);
	if (parse->redir)
		free_parse(parse->redir);
	free(parse);
	parse = NULL;
}

int		check_sem(t_tokenizer *tokens)
{
	if (tokens->tokens[tokens->tok_i] && tokens->tokens[tokens->tok_i][0] == ';')
		return (1);
	return (0);
}

t_parser	*check_pipe(t_minishell *mini, t_tokenizer *tokens)
{
	t_parser	*parse;

	if (tokens->tokens[tokens->tok_i] && tokens->tokens[tokens->tok_i][0] == '|')
	{
		parse = parser(mini, tokens);
		return (parse);
	}
	return (NULL);
}

void		check_redir_left(t_minishell *mini, t_tokenizer *tokens, t_parser *pars)
{
	tokens->tok_i++;
	while (tokens->tokens[++tokens->tok_i] || !ft_strchr(SYM_CHAR, tokens->tokens[tokens->tok_i][0]))
	{
		if (!pars->cmd)
		{
			if (!(pars->cmd = ft_strdup(tokens->tokens[tokens->tok_i])))
				exit(ERROR_BAD_MALLOC);
		}
		else
		{
			if (!(pars->arg[pars->i_arg++] = ft_strdup(tokens->tokens[tokens->tok_i])))
				exit(ERROR_BAD_MALLOC);
		}
	}
}

t_parser	*check_redir(t_minishell *mini, t_tokenizer *tokens, t_parser *pars)
{
	t_parser	*parse;

	if (tokens->tokens[tokens->tok_i] && (tokens->tokens[tokens->tok_i][0] == '<' || tokens->tokens[tokens->tok_i][0] == '>'))
	{
		if (!(parse = (t_parser*)ft_calloc(sizeof(t_parser), 1)) \
		|| !(parse->ard_red = ft_strdup(tokens->tokens[tokens->tok_i + 1])))
			exit(ERROR_BAD_MALLOC);
		if (tokens->tokens[tokens->tok_i][0] == '<' && tokens->tokens[tokens->tok_i][1] == '\0')
		{
			parse->type = 1;
			tokens->tok_i++;
			while (tokens->tokens[++tokens->tok_i] && !ft_strchr(SYM_CHAR, tokens->tokens[tokens->tok_i][0]))
			{
				if (!pars->cmd)
				{
					if (!(pars->cmd = ft_strdup(tokens->tokens[tokens->tok_i])))
						exit(ERROR_BAD_MALLOC);
				}
				else
				{
					if (!(pars->arg[pars->i_arg++] = ft_strdup(tokens->tokens[tokens->tok_i])))
						exit(ERROR_BAD_MALLOC);
				}
				if (!tokens->tokens[tokens->tok_i + 1])
					break ;
			}
		}
		else if (tokens->tokens[tokens->tok_i][0] == '>' && tokens->tokens[tokens->tok_i][1] == '\0')
		{
			parse->type = 2;
			tokens->tok_i++;
			while (tokens->tokens[++tokens->tok_i] && !ft_strchr(SYM_CHAR, tokens->tokens[tokens->tok_i][0]))
			{
				if (!pars->cmd)
				{
					if (!(pars->cmd = ft_strdup(tokens->tokens[tokens->tok_i])))
						exit(ERROR_BAD_MALLOC);
				}
				else
				{
					if (!(pars->arg[pars->i_arg++] = ft_strdup(tokens->tokens[tokens->tok_i])))
						exit(ERROR_BAD_MALLOC);
				}
				if (!tokens->tokens[tokens->tok_i + 1])
					break ;
			}
		}
		else if (tokens->tokens[tokens->tok_i][0] == '>' && tokens->tokens[tokens->tok_i][1] == '>' \
		&& tokens->tokens[tokens->tok_i][2] == '\0')
		{
			parse->type = 3;
			tokens->tok_i++;
			while (tokens->tokens[++tokens->tok_i] && !ft_strchr(SYM_CHAR, tokens->tokens[tokens->tok_i][0]))
			{
				if (!pars->cmd)
				{
					if (!(pars->cmd = ft_strdup(tokens->tokens[tokens->tok_i])))
						exit(ERROR_BAD_MALLOC);
				}
				else
				{
					if (!(pars->arg[pars->i_arg++] = ft_strdup(tokens->tokens[tokens->tok_i])))
						exit(ERROR_BAD_MALLOC);
				}
				if (!tokens->tokens[tokens->tok_i + 1])
					break ;
			}
		}
		if (check_sem(tokens) || (pars->pipe = check_pipe(mini, tokens))
		|| (parse->redir = check_redir(mini, tokens, pars)))
			return (parse);
		return (parse);
	}
	return (NULL);
}

int			parser_utils(t_minishell *mini, t_tokenizer *tokens, \
			t_parser *parse)
{
	if (check_sem(tokens) || (parse->pipe = check_pipe(mini, tokens))
	|| (parse->redir = check_redir(mini, tokens, parse)))
		return (1);
	if (!parse->cmd)
	{
		if (!(parse->cmd = ft_strdup(tokens->tokens[tokens->tok_i])))
			exit(ERROR_BAD_MALLOC);
	}
	else
	{
		if (!(parse->arg[parse->i_arg++] = \
		ft_strdup(tokens->tokens[tokens->tok_i])))
			exit(ERROR_BAD_MALLOC);
	}
	return (0);
}

t_parser	*parser(t_minishell *mini, t_tokenizer *tokens)
{
	t_parser	*parse;

	if (!(parse = (t_parser*)ft_calloc(sizeof(t_parser), 1)) \
	|| !(parse->arg = (char**)ft_calloc(sizeof(char*), tokens->len_token + 1)) \
	|| !(parse->arg[0] = ft_strdup("")))
		exit(ERROR_BAD_MALLOC);
	parse->i_arg = 1;
	while (tokens->tokens[++tokens->tok_i])
	{
		if (parser_utils(mini, tokens, parse))
			break ;
	}
	parse->arg[parse->i_arg] = NULL;
	return (parse);
}

void	my_print_red(t_parser *parse)
{
	printf("arg_red: %s\n", parse->ard_red);
	printf("type: %d\n", parse->type);
	printf("next\n");
	if (parse->pipe)
		my_print(parse->pipe);
	if (parse->redir)
		my_print_red(parse->redir);
}

void	my_print(t_parser *parse)
{
	int i = -1;
	printf("cmd: %s\n", parse->cmd);
	while (parse->arg[++i] && i < parse->i_arg)
		printf("arg%d: %s\n", i, parse->arg[i]);
	printf("next\n");
	if (parse->pipe)
		my_print(parse->pipe);
	if (parse->redir)
		my_print_red(parse->redir);
}
