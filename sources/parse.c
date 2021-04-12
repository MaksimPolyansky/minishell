/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 11:16:32 by heusebio          #+#    #+#             */
/*   Updated: 2021/01/30 21:39:27 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		free_tokens(t_tokenizer *tokens)
{
	free_line_tokens(tokens);
	free_dline_tokens(tokens);
}

void		free_dline_parse(t_parser *parse)
{
	int		i;

	if (parse->arg)
	{
		i = 0;
		while (parse->arg[i])
		{
			free(parse->arg[i]);
			parse->arg[i++] = NULL;
		}
		free(parse->arg);
	}
	parse->arg = NULL;
}

void		parse_clear(t_parser *parse)
{
	parse->arg = NULL;
	parse->cmd = NULL;
	parse->i_arg = 0;
	parse->pipe = NULL;
	parse->redir = NULL;
	parse->type = 0;
}

int			parser_utils(t_minishell *mini, t_tokenizer *tokens, \
			t_parser *parse)
{
	if (tokens->fail == 0)
	{
		if ((check_sem(tokens) || (parse->pipe = check_pipe(mini, tokens))
		|| (parse->redir = check_redir(mini, tokens, parse))))
			return (1);
	}
	tokens->fail = 0;
	if (!parse->cmd && tokens->tokens[tokens->tok_i][0] != '\0')
	{
		if (!(parse->cmd = ft_strdup(tokens->tokens[tokens->tok_i])))
			error_tokens(tokens, parse);
	}
	else if (parse->cmd && tokens->tokens[tokens->tok_i][0] != '\0')
	{
		if (!(parse->arg[parse->i_arg++] = \
		ft_strdup(tokens->tokens[tokens->tok_i])))
			error_tokens(tokens, parse);
	}
	return (0);
}

t_parser	*parser(t_minishell *mini, t_tokenizer *tokens)
{
	t_parser	*parse;

	if (!(parse = (t_parser*)ft_calloc(sizeof(t_parser), 1)) \
	|| !(parse->arg = (char**)ft_calloc(sizeof(char*), tokens->len_token + 1)) \
	|| !(parse->arg[0] = ft_strdup("")))
		error_tokens(tokens, NULL);
	parse->i_arg = 1;
	while (tokens->tokens[++tokens->tok_i])
	{
		tokenizer(mini, parse, tokens);
		if (parser_utils(mini, tokens, parse))
			break ;
	}
	parse->arg[parse->i_arg] = NULL;
	parse->i_arg--;
	return (parse);
}
