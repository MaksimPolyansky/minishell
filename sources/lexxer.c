/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexxer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 11:22:23 by heusebio          #+#    #+#             */
/*   Updated: 2021/01/30 21:04:00 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		maybe_pipe(t_tokenizer *tokens, t_minishell *mini)
{
	if (mini->input[mini->line_i] == '|')
	{
		if (tokens->line[ft_strlen(tokens->line) - 1] != '\n' \
		&& tokens->line[0] != '\0')
			if (!(tokens->line = ft_charjoin(&tokens->line, '\n')))
				error_tokens(tokens, NULL);
		if (!(tokens->line = ft_charjoin(&tokens->line, \
		mini->input[mini->line_i++])))
			error_tokens(tokens, NULL);
		if (!(tokens->line = ft_charjoin(&tokens->line, '\n')))
			error_tokens(tokens, NULL);
	}
	return (0);
}

int		maybe_redir(t_tokenizer *tokens, t_minishell *mini)
{
	if (mini->input[mini->line_i] == '>' || mini->input[mini->line_i] == '<')
	{
		if (tokens->line[ft_strlen(tokens->line) - 1] != '\n' \
		&& tokens->line[0] != '\0')
			tokens->line = ft_charjoin(&tokens->line, '\n');
		while (ft_strchr(ONLY_REDIR, mini->input[mini->line_i]))
		{
			if (!(tokens->line = ft_charjoin(&tokens->line, \
			mini->input[mini->line_i++])))
				error_tokens(tokens, NULL);
		}
		if (!(tokens->line = ft_charjoin(&tokens->line, '\n')))
			error_tokens(tokens, NULL);
	}
	return (0);
}

int		lexxer_next(t_tokenizer *tokens)
{
	int		i;

	if (!(tokens->tokens = ft_split(tokens->line, '\n')))
		error_tokens(tokens, NULL);
	i = -1;
	tokens->len_token = 1;
	while (tokens->line[++i] != '\0')
	{
		if (tokens->line[i] == '\n')
			tokens->len_token++;
	}
	free_line_tokens(tokens);
	return (1);
}

int		lexxer_utils(t_minishell *mini, t_tokenizer *tokens)
{
	if (mini->input[mini->line_i] == 39 \
	|| mini->input[mini->line_i] == 34)
		dquote_or_quote(mini, tokens);
	else if (maybe_sem(tokens, mini) || maybe_pipe(tokens, mini) \
	|| maybe_redir(tokens, mini))
		return (lexxer_next(tokens));
	else if (maybe_shield(mini, NULL, NULL, mini->line_i))
	{
		if (!(tokens->line = ft_charjoin(&tokens->line, \
		mini->input[mini->line_i++])) \
		|| !(tokens->line = ft_charjoin(&tokens->line, \
		mini->input[mini->line_i++])))
			error_tokens(tokens, NULL);
		return (0);
	}
	else if (!ft_strchr(SYM_CHAR, mini->input[mini->line_i]) \
	&& mini->input[mini->line_i] != ' ')
	{
		if (!(tokens->line = ft_charjoin(&tokens->line, \
		mini->input[mini->line_i++])))
			error_tokens(tokens, NULL);
	}
	return (0);
}

int		lexxer(t_minishell *mini, t_tokenizer *tokens)
{
	if (check_before_lexxer(mini, tokens))
		return (0);
	if (!(tokens->line = ft_strdup("")))
		error_tokens(tokens, NULL);
	while (mini->input[mini->line_i] != '\0')
	{
		if (skipping_spaces(mini, tokens, 'a') \
		&& tokens->line[ft_strlen(tokens->line) - 1] != '\n')
			tokens->line = ft_charjoin(&tokens->line, '\n');
		while (mini->input[mini->line_i] != '\0' \
		&& mini->input[mini->line_i] != ' ')
			if (lexxer_utils(mini, tokens))
				return (1);
	}
	return (lexxer_next(tokens));
}
