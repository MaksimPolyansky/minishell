/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 11:17:22 by heusebio          #+#    #+#             */
/*   Updated: 2021/01/30 21:04:24 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		check_redir_left(t_tokenizer *tokens, t_parser *pars)
{
	tokens->tok_i++;
	while (tokens->tokens[++tokens->tok_i] \
	|| !ft_strchr(SYM_CHAR, tokens->tokens[tokens->tok_i][0]))
		redir_utils(pars, tokens);
}

t_parser	*redir_left(t_minishell *mini, t_tokenizer *tokens, t_parser *pars)
{
	t_parser	*parse;

	if (!(parse = (t_parser*)ft_calloc(sizeof(t_parser), 1)))
		error_tokens(tokens, pars);
	++tokens->tok_i;
	parse->type = 1;
	tokenizer(mini, parse, tokens);
	if (!(parse->arg_red = ft_strdup(tokens->tokens[tokens->tok_i])))
		error_tokens(tokens, pars);
	while (tokens->tokens[++tokens->tok_i] && !ft_strchr(SYM_CHAR, \
	tokens->tokens[tokens->tok_i][0]))
	{
		tokenizer(mini, parse, tokens);
		redir_utils(pars, tokens);
		if (!tokens->tokens[tokens->tok_i + 1])
			break ;
	}
	return (parse);
}

t_parser	*redir_right(t_minishell *mini, \
			t_tokenizer *tokens, t_parser *pars)
{
	t_parser	*parse;

	if (!(parse = (t_parser*)ft_calloc(sizeof(t_parser), 1)))
		error_tokens(tokens, pars);
	++tokens->tok_i;
	parse->type = 2;
	tokenizer(mini, parse, tokens);
	if (!(parse->arg_red = ft_strdup(tokens->tokens[tokens->tok_i])))
		error_tokens(tokens, pars);
	while (tokens->tokens[++tokens->tok_i] && !ft_strchr(SYM_CHAR, \
	tokens->tokens[tokens->tok_i][0]))
	{
		tokenizer(mini, parse, tokens);
		redir_utils(pars, tokens);
		if (!tokens->tokens[tokens->tok_i + 1])
			break ;
	}
	return (parse);
}

t_parser	*redir_dright(t_minishell *mini, \
			t_tokenizer *tokens, t_parser *pars)
{
	t_parser	*parse;

	if (!(parse = (t_parser*)ft_calloc(sizeof(t_parser), 1)))
		error_tokens(tokens, pars);
	++tokens->tok_i;
	parse->type = 3;
	tokenizer(mini, parse, tokens);
	if (!(parse->arg_red = ft_strdup(tokens->tokens[tokens->tok_i])))
		error_tokens(tokens, pars);
	while (tokens->tokens[++tokens->tok_i] && !ft_strchr(SYM_CHAR, \
	tokens->tokens[tokens->tok_i][0]))
	{
		tokenizer(mini, parse, tokens);
		redir_utils(pars, tokens);
		if (!tokens->tokens[tokens->tok_i + 1])
			break ;
	}
	return (parse);
}

t_parser	*check_redir(t_minishell *mini, \
			t_tokenizer *tokens, t_parser *pars)
{
	t_parser	*parse;

	if (tokens->tokens[tokens->tok_i] && (((tokens->tokens[tokens->tok_i][0] ==
	'<' || tokens->tokens[tokens->tok_i][0] == '>') && tokens->tokens[tokens->
	tok_i][1] == '\0') || (tokens->tokens[tokens->tok_i][0] == '>' \
	&& tokens->tokens[tokens->tok_i][1] == '>' \
	&& tokens->tokens[tokens->tok_i][2] == '\0')))
	{
		if (tokens->tokens[tokens->tok_i][0] == '<' \
		&& tokens->tokens[tokens->tok_i][1] == '\0')
			parse = redir_left(mini, tokens, pars);
		else if (tokens->tokens[tokens->tok_i][0] == '>' \
		&& tokens->tokens[tokens->tok_i][1] == '\0')
			parse = redir_right(mini, tokens, pars);
		else if (tokens->tokens[tokens->tok_i][0] == '>' \
		&& tokens->tokens[tokens->tok_i][1] == '>' \
		&& tokens->tokens[tokens->tok_i][2] == '\0')
			parse = redir_dright(mini, tokens, pars);
		if (check_sem(tokens) || (pars->pipe = check_pipe(mini, tokens))
		|| (parse->redir = check_redir(mini, tokens, pars)))
			return (parse);
		return (parse);
	}
	return (NULL);
}
