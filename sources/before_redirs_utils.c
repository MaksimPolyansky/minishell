/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_redirs_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 11:27:17 by heusebio          #+#    #+#             */
/*   Updated: 2021/01/30 21:03:38 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		quotes(t_minishell *mini, t_tokenizer *tokens)
{
	char	c;

	if (mini->input[tokens->line_i] == 39 || mini->input[tokens->line_i] == 34)
	{
		c = mini->input[tokens->line_i];
		while (mini->input[++tokens->line_i] != c)
		{
			if (!mini->input[tokens->line_i])
				return (1);
			if (mini->input[tokens->line_i] == '\\')
			{
				if (mini->input[++tokens->line_i] == 39 && c == 39)
					break ;
			}
		}
		++tokens->line_i;
	}
	return (0);
}

int		before_spaces(t_minishell *mini, t_tokenizer *tokens, int c)
{
	int		i;

	i = tokens->line_i - 1;
	while (i >= 0 && mini->input[i] == ' ')
		i--;
	if (maybe_before_shield(mini, i) && c == 6)
		return (1);
	if (i != -1 && ft_strchr(ONLY_REDIR, mini->input[i]) && c == 5)
		return (1);
	if (i != -1 && ft_strchr(SYM_CHAR, mini->input[i]) && c == 4)
		return (1);
	if (i != -1 && mini->input[i] == '|' && c == 3)
		return (1);
	if (i != -1 && mini->input[i] == ';' && c == 2)
		return (1);
	if (i == -1 && c == 1)
		return (1);
	return (0);
}

int		pipes(t_minishell *mini, t_tokenizer *tokens)
{
	if (mini->input[tokens->line_i] == '|')
	{
		if (mini->input[tokens->line_i + 1] == '|')
			return (error_before_lexxer(mini, SEPT));
		else if (before_spaces(mini, tokens, 1) \
		|| ((before_spaces(mini, tokens, 4)) \
		&& !before_spaces(mini, tokens, 6)))
			return (error_before_lexxer(mini, SEPO));
		tokens->line_i++;
		if (skip_space(mini, tokens, 'e') \
		|| ft_strchr(SYM_CHAR, mini->input[tokens->line_i]))
			return (error_before_lexxer(mini, SEPO));
	}
	return (1);
}

int		sems(t_minishell *mini, t_tokenizer *tokens)
{
	if (mini->input[tokens->line_i] == ';')
	{
		if (mini->input[tokens->line_i + 1] == ';')
			return (error_before_lexxer(mini, SEST));
		else if (before_spaces(mini, tokens, 1) \
		|| (before_spaces(mini, tokens, 5) && !before_spaces(mini, tokens, 6)))
			return (error_before_lexxer(mini, SESO));
		tokens->line_i++;
		if (skip_space(mini, tokens, 'b'))
			return (error_before_lexxer(mini, SESO));
		else if (skip_space(mini, tokens, 'c'))
			return (pipes(mini, tokens));
	}
	return (1);
}

int		check_left1(t_minishell *mini, t_tokenizer *tokens)
{
	int		i;

	i = 0;
	while (mini->input[tokens->line_i + i] == '<')
		i++;
	if (i == 1 || i == 2 || i == 3)
	{
		tokens->line_i += i;
		if (skip_space(mini, tokens, 'c'))
			return (pipes(mini, tokens));
		else if (skip_space(mini, tokens, 'b'))
			return (sems(mini, tokens));
		if (i == 1)
			return (1);
		return (0);
	}
	if (i == 4)
		return (error_before_lexxer(mini, SERL));
	if (i == 5)
		return (error_before_lexxer(mini, SERDL));
	else
		return (error_before_lexxer(mini, SERTL));
}
