/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 11:01:03 by heusebio          #+#    #+#             */
/*   Updated: 2021/01/30 21:05:36 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_tokens(t_tokenizer *tokens, t_parser *parse)
{
	if (tokens)
		free_tokens(tokens);
	if (parse)
		free_parse(parse);
	exit(EXIT_FAILURE);
}

void	tokens_clear(t_tokenizer *tokens)
{
	tokens->tok_i = 0;
	tokens->line = NULL;
	tokens->len_token = 0;
	tokens->tokens = NULL;
	tokens->line_i = 0;
	tokens->fail = 0;
}

int		no_print_chield(t_tokenizer *tokens)
{
	if (tokens->tokens[tokens->tok_i][tokens->line_i + 1] == '$' \
		|| tokens->tokens[tokens->tok_i][tokens->line_i + 1] == '\\' \
		|| tokens->tokens[tokens->tok_i][tokens->line_i + 1] == '|' \
		|| tokens->tokens[tokens->tok_i][tokens->line_i + 1] == ';' \
		|| tokens->tokens[tokens->tok_i][tokens->line_i + 1] == '`' \
		|| tokens->tokens[tokens->tok_i][tokens->line_i + 1] == '~' \
		|| tokens->tokens[tokens->tok_i][tokens->line_i + 1] == 39 \
		|| tokens->tokens[tokens->tok_i][tokens->line_i + 1] == 34 \
		|| tokens->tokens[tokens->tok_i][tokens->line_i + 1] == '>' \
		|| tokens->tokens[tokens->tok_i][tokens->line_i + 1] == '<' \
		|| tokens->tokens[tokens->tok_i][tokens->line_i + 1] == ' ')
		return (1);
	return (0);
}

void	sort_shield(t_tokenizer *tokens)
{
	if (tokens->tokens[tokens->tok_i][tokens->line_i] == '\\')
	{
		if (no_print_chield(tokens))
		{
			if (!(tokens->line = ft_charjoin(&tokens->line, \
			tokens->tokens[tokens->tok_i][++tokens->line_i])))
				error_tokens(tokens, NULL);
			tokens->fail = 1;
		}
		else
		{
			if (!(tokens->line = ft_charjoin(&tokens->line, \
			tokens->tokens[tokens->tok_i][++tokens->line_i])) \
			|| !(tokens->line = ft_charjoin(&tokens->line, \
			tokens->tokens[tokens->tok_i][++tokens->line_i])))
				error_tokens(tokens, NULL);
		}
	}
}

void	tokenizer(t_minishell *mini, t_parser *parse, t_tokenizer *tokens)
{
	if (!(tokens->line = ft_strdup("")))
		error_tokens(tokens, parse);
	tokens->line_i = -1;
	while (tokens->tokens[tokens->tok_i] \
	&& tokens->tokens[tokens->tok_i][++tokens->line_i] != '\0')
	{
		if (tokens->tokens[tokens->tok_i][tokens->line_i] == 39)
			sort_quote(tokens, tokens->tokens[tokens->tok_i]);
		else if (tokens->tokens[tokens->tok_i][tokens->line_i] == 34)
			sort_dquote(mini, tokens, tokens->tokens[tokens->tok_i]);
		else if (tokens->tokens[tokens->tok_i][tokens->line_i] == 36)
			sort_dollar(mini, parse, tokens);
		else if (maybe_shield(NULL, tokens, NULL, 0))
			sort_shield(tokens);
		else
		{
			if (!(tokens->line = ft_charjoin(&tokens->line, \
			tokens->tokens[tokens->tok_i][tokens->line_i])))
				error_tokens(tokens, parse);
		}
	}
	free(tokens->tokens[tokens->tok_i]);
	if (!(tokens->tokens[tokens->tok_i] = ft_strdup(tokens->line)))
		error_tokens(tokens, parse);
	free_line_tokens(tokens);
}
