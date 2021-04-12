/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 11:26:31 by heusebio          #+#    #+#             */
/*   Updated: 2021/01/30 21:03:44 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_left2(t_minishell *mini, t_tokenizer *tokens)
{
	int		i;

	i = 0;
	while (mini->input[tokens->line_i + i] == '<')
		i++;
	if (i == 1)
		return (error_before_lexxer(mini, SERL));
	if (i == 2)
		return (error_before_lexxer(mini, SERDL));
	else
		return (error_before_lexxer(mini, SERTL));
}

int		redirs_left(t_minishell *mini, t_tokenizer *tokens)
{
	if (before_spaces(mini, tokens, 6) || !before_spaces(mini, tokens, 5))
	{
		if (!check_left1(mini, tokens))
			return (0);
		else if (skip_space(mini, tokens, 'e'))
			return (error_before_lexxer(mini, SERALONE));
		if (mini->input[tokens->line_i - 1] == ' ')
			tokens->line_i--;
	}
	else if (before_spaces(mini, tokens, 5) && !before_spaces(mini, tokens, 6))
		return (check_left2(mini, tokens));
	return (1);
}

int		redirs_right1(t_minishell *mini, t_tokenizer *tokens, int c)
{
	if (c == 1)
	{
		tokens->line_i++;
		if (mini->input[tokens->line_i] == '|' \
		|| skip_space(mini, tokens, 'e'))
			return (error_before_lexxer(mini, SERALONE));
		else if (skip_space(mini, tokens, 'b'))
			return (sems(mini, tokens));
		else if (skip_space(mini, tokens, 'c'))
			return (pipes(mini, tokens));
	}
	if (c == 2)
	{
		tokens->line_i += 2;
		if (skip_space(mini, tokens, 'e'))
			return (error_before_lexxer(mini, SERALONE));
		if (skip_space(mini, tokens, 'b'))
			return (sems(mini, tokens));
		else if (skip_space(mini, tokens, 'c'))
			return (pipes(mini, tokens));
	}
	if (mini->input[tokens->line_i - 1] == ' ')
		tokens->line_i--;
	return (1);
}

int		redirs_right(t_minishell *mini, t_tokenizer *tokens)
{
	int		i;

	i = 0;
	while (mini->input[tokens->line_i + i] == '>')
		i++;
	if (i == 1)
		return (redirs_right1(mini, tokens, 1));
	if (i == 2)
		return (redirs_right1(mini, tokens, 2));
	if (i == 3)
	{
		if (mini->input[tokens->line_i + i] == '|')
			return (error_before_lexxer(mini, SERRP));
		return (error_before_lexxer(mini, SERR));
	}
	else if (i >= 4)
		return (error_before_lexxer(mini, SERDR));
	return (1);
}

int		redirs(t_minishell *mini, t_tokenizer *tokens)
{
	if (mini->input[tokens->line_i] == '<')
		return (redirs_left(mini, tokens));
	else if (mini->input[tokens->line_i] == '>')
	{
		if (!before_spaces(mini, tokens, 5))
			return (redirs_right(mini, tokens));
		else
			return (redirs_right_error(mini, tokens));
	}
	return (1);
}
