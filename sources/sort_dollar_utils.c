/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_dollar_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 11:06:09 by heusebio          #+#    #+#             */
/*   Updated: 2021/01/30 21:04:29 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sort_quote(t_tokenizer *tokens, char *line)
{
	while (line[++tokens->line_i] != 39 && line[tokens->line_i])
	{
		if (!(tokens->line = ft_charjoin(&tokens->line, line[tokens->line_i])))
			error_tokens(tokens, NULL);
	}
}

int		maybe_shield(t_minishell *mini, t_tokenizer *tokens, \
		t_parser *parse, int len)
{
	if (mini && !tokens && !parse)
	{
		if (mini->input[len] == '\\')
		{
			if (ft_isprint(mini->input[len + 1]) \
			|| mini->input[len + 1] == ' ')
				return (1);
		}
	}
	if (!mini && !parse && len == 0 \
	&& tokens->tokens[tokens->tok_i][tokens->line_i] == '\\')
	{
		if (ft_isprint(tokens->tokens[tokens->tok_i][tokens->line_i + 1]) \
		|| tokens->tokens[tokens->tok_i][tokens->line_i + 1] == ' ')
			return (1);
	}
	return (0);
}

int		one_sort_after_dollar(char c)
{
	if (c == 33 || c == '@' || ft_isdigit(c) || c == 42)
		return (1);
	if (c == '?')
		return (2);
	return (0);
}

void	check_env(t_minishell *mini, t_tokenizer *tokens, char *line)
{
	int		i;
	char	*str;
	char	*tmp;

	i = -1;
	while (mini->env[++i])
	{
		if (!(ft_strncmp(mini->env[i], line, ft_strlen(line))) \
		&& mini->env[i][ft_strlen(line)] == '=')
		{
			if (!(tmp = ft_substr(mini->env[i], ft_strlen(line) + 1, \
			ft_strlen(mini->env[i]) - ft_strlen(line) - 1)))
				error_tokens(tokens, NULL);
			str = tokens->line;
			if (!(tokens->line = ft_strjoin(str, tmp)))
				error_tokens(tokens, NULL);
			free(str);
			free(tmp);
			return ;
		}
	}
}

void	add_exec_stat(t_minishell *mini, t_tokenizer *tokens)
{
	char	*str;
	char	*tmp;

	tokens->line_i++;
	if (!(tmp = ft_itoa(mini->exec_stat)))
		error_tokens(tokens, NULL);
	mini->exec_stat = 0;
	str = tokens->line;
	if (!(tokens->line = ft_strjoin(str, tmp)))
		error_tokens(tokens, NULL);
	free(str);
	free(tmp);
}
