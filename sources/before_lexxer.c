/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_lexxer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 11:25:44 by heusebio          #+#    #+#             */
/*   Updated: 2021/01/30 21:03:30 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		error_before_lexxer(t_minishell *mini, char *fail)
{
	mini->exec_stat = 258;
	ft_putendl_fd(fail, 2);
	return (0);
}

int		maybe_before_shield(t_minishell *mini, int len)
{
	if (ft_isprint(mini->input[len]) && len != 0 \
	&& mini->input[len - 1] == '\\')
		return (1);
	return (0);
}

int		skip_space(t_minishell *mini, t_tokenizer *tokens, char c)
{
	while (mini->input[tokens->line_i] == ' ' && mini->input[tokens->line_i])
		tokens->line_i++;
	if (mini->input[tokens->line_i] == '\0' && c == 'e')
		return (1);
	if (mini->input[tokens->line_i] == '|' && c == 'c')
		return (1);
	if (mini->input[tokens->line_i] == ';' && c == 'b')
		return (1);
	if (maybe_shield(mini, NULL, NULL, tokens->line_i) && c == 'a')
		return (1);
	return (0);
}

int		check_before_lexxer(t_minishell *mini, t_tokenizer *tokens)
{
	if (skip_space(mini, tokens, 'e'))
		return (1);
	while (mini->input[tokens->line_i] != '\0')
	{
		if (skip_space(mini, tokens, 'e'))
			break ;
		if (mini->input[tokens->line_i] == 34 \
		|| mini->input[tokens->line_i] == 39 \
		|| mini->input[tokens->line_i] == '|' \
		|| mini->input[tokens->line_i] == ';' \
		|| mini->input[tokens->line_i] == '>' \
		|| mini->input[tokens->line_i] == '<')
		{
			if (check_error_syntax(mini, tokens))
				return (1);
		}
		else if (mini->input[tokens->line_i] == '\\' \
		&& mini->input[tokens->line_i + 1] == '\0')
			return (1);
		else if (maybe_shield(mini, NULL, NULL, tokens->line_i))
			tokens->line_i += 2;
		else
			tokens->line_i++;
	}
	return (0);
}

int		redirs_right_error(t_minishell *mini, t_tokenizer *tokens)
{
	int		i;

	i = 0;
	while (mini->input[tokens->line_i + i] == '>')
		i++;
	if (i == 1)
		return (error_before_lexxer(mini, SERR));
	else
		return (error_before_lexxer(mini, SERDR));
	return (1);
}
