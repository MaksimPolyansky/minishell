/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexxer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 11:23:05 by heusebio          #+#    #+#             */
/*   Updated: 2021/01/30 21:03:55 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		error_lexxer(t_minishell *mini, t_tokenizer *tokens, char *fail)
{
	free(tokens->line);
	tokens->line = NULL;
	mini->exec_stat = 258;
	ft_putendl_fd(fail, 2);
	return (0);
}

void	dquote_or_quote(t_minishell *mini, t_tokenizer *tokens)
{
	char	c;

	c = mini->input[mini->line_i];
	tokens->line = ft_charjoin(&tokens->line, mini->input[mini->line_i]);
	while (mini->input[++mini->line_i] != c)
	{
		if (mini->input[mini->line_i] == '\\')
		{
			tokens->line = ft_charjoin(&tokens->line, \
			mini->input[mini->line_i++]);
			if (mini->input[mini->line_i] == 39 && c == 39)
				break ;
			tokens->line = ft_charjoin(&tokens->line, \
			mini->input[mini->line_i]);
		}
		else
			tokens->line = ft_charjoin(&tokens->line, \
			mini->input[mini->line_i]);
	}
	tokens->line = ft_charjoin(&tokens->line, mini->input[mini->line_i++]);
}

int		skipping_spaces(t_minishell *mini, t_tokenizer *tokens, char c)
{
	while (mini->input[mini->line_i] == ' ' && mini->input[mini->line_i])
		mini->line_i++;
	if (mini->input[mini->line_i] && *tokens->line != '\0' && c == 'a')
		return (1);
	if (mini->input[mini->line_i] == ';' && c == 'b')
		return (1);
	if (mini->input[mini->line_i] == '|' && c == 'c')
		return (1);
	if ((mini->input[mini->line_i] == '>' || \
	mini->input[mini->line_i] == '<') && c == 'd')
		return (1);
	if (mini->input[mini->line_i] == '\0' && c == 'e')
		return (1);
	return (0);
}

int		maybe_sem(t_tokenizer *tokens, t_minishell *mini)
{
	if (mini->input[mini->line_i] == ';')
	{
		if (tokens->line[ft_strlen(tokens->line) - 1] != '\n' \
		&& tokens->line[0] != '\0')
			if (!(tokens->line = ft_charjoin(&tokens->line, '\n')))
				error_tokens(tokens, NULL);
		if (!(tokens->line = ft_charjoin(&tokens->line, \
		mini->input[mini->line_i++])))
			error_tokens(tokens, NULL);
		return (1);
	}
	return (0);
}
