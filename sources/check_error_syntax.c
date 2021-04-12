/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 21:05:52 by heusebio          #+#    #+#             */
/*   Updated: 2021/01/30 21:03:50 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_error_syntax(t_minishell *mini, t_tokenizer *tokens)
{
	if (mini->input[tokens->line_i] == 34 \
	|| mini->input[tokens->line_i] == 39)
	{
		if (quotes(mini, tokens))
			return (1);
	}
	else if (mini->input[tokens->line_i] == '|')
	{
		if (!pipes(mini, tokens))
			return (1);
	}
	else if (mini->input[tokens->line_i] == ';')
	{
		if (!sems(mini, tokens))
			return (1);
	}
	else if (mini->input[tokens->line_i] == '>' \
	|| mini->input[tokens->line_i] == '<')
	{
		if (!redirs(mini, tokens))
			return (1);
	}
	return (0);
}
