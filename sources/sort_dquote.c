/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_dquote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 11:04:35 by heusebio          #+#    #+#             */
/*   Updated: 2021/01/30 21:04:43 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sort_dollar_dquote1(t_minishell *mini, t_tokenizer *tokens, \
char *line, char **cash)
{
	if (ft_isalpha(line[tokens->line_i + 1]) \
	|| line[tokens->line_i + 1] == '_')
	{
		while (line[++tokens->line_i] && (ft_isalpha(line[tokens->line_i]) \
		|| ft_isdigit(line[tokens->line_i]) || line[tokens->line_i] == '_'))
		{
			if (!((*cash) = ft_charjoin(cash, line[tokens->line_i])))
				error_tokens(tokens, NULL);
		}
		check_env(mini, tokens, (*cash));
		--tokens->line_i;
	}
	else
	{
		if (!(tokens->line = ft_charjoin(&tokens->line, line[tokens->line_i])))
			error_tokens(tokens, NULL);
	}
}

void	sort_dollar_dquote(t_minishell *mini, t_tokenizer *tokens, char *line)
{
	char	*cash;

	if (!(cash = ft_strdup("")))
		error_tokens(tokens, NULL);
	if (one_sort_after_dollar(line[tokens->line_i + 1]) == 1)
	{
		if (!(cash = ft_charjoin(&cash, line[++tokens->line_i])))
			error_tokens(tokens, NULL);
		check_env(mini, tokens, cash);
	}
	else if (one_sort_after_dollar(line[tokens->line_i + 1]) == 2)
		add_exec_stat(mini, tokens);
	else
		sort_dollar_dquote1(mini, tokens, line, &cash);
	free(cash);
}

int		check_shield_dquote(t_tokenizer *tokens)
{
	if (tokens->tokens[tokens->tok_i][tokens->line_i] == '\\')
	{
		if (tokens->tokens[tokens->tok_i][tokens->line_i + 1] == '$' \
		|| tokens->tokens[tokens->tok_i][tokens->line_i + 1] == '\\' \
		|| tokens->tokens[tokens->tok_i][tokens->line_i + 1] == '`' \
		|| tokens->tokens[tokens->tok_i][tokens->line_i + 1] == 34)
		{
			if (!(tokens->line = ft_charjoin(&tokens->line, \
			tokens->tokens[tokens->tok_i][++tokens->line_i])))
				error_tokens(tokens, NULL);
		}
		else
		{
			if (!(tokens->line = ft_charjoin(&tokens->line, \
			tokens->tokens[tokens->tok_i][tokens->line_i])) \
			|| !(tokens->line = ft_charjoin(&tokens->line, \
			tokens->tokens[tokens->tok_i][++tokens->line_i])))
				error_tokens(tokens, NULL);
		}
		return (1);
	}
	return (0);
}

void	sort_dquote(t_minishell *mini, t_tokenizer *tokens, char *line)
{
	while (line[++tokens->line_i] != 34 && line[tokens->line_i])
	{
		if (line[tokens->line_i] == 36)
			sort_dollar_dquote(mini, tokens, line);
		else if (check_shield_dquote(tokens))
			;
		else
			tokens->line = ft_charjoin(&tokens->line, line[tokens->line_i]);
	}
}
