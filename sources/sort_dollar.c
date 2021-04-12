/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 11:02:56 by heusebio          #+#    #+#             */
/*   Updated: 2021/01/30 21:05:41 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		after_dollar_alone(t_minishell *mini, t_parser *parse, \
		t_tokenizer *tokens, char **cash)
{
	char	c;

	c = tokens->tokens[tokens->tok_i][tokens->line_i + 1];
	if (c == 33 || c == '@' || ft_isdigit(c) || c == 42)
	{
		if (!((*cash) = ft_charjoin(cash, \
		tokens->tokens[tokens->tok_i][++tokens->line_i])))
			error_tokens(tokens, parse);
		return (1);
	}
	else if (c == '?')
	{
		add_exec_stat(mini, tokens);
		return (1);
	}
	return (0);
}

void	check_env_dollar1(t_parser *parse, \
		t_tokenizer *tokens, char *line)
{
	char *str;

	parse->fail = 1;
	if (!(tokens->line = ft_charjoin(&tokens->line, '$')))
		error_tokens(tokens, parse);
	str = tokens->line;
	if (!(tokens->line = ft_strjoin(str, line)))
		error_tokens(tokens, parse);
	free(str);
}

void	check_env_dollar(t_minishell *mini, t_parser *parse, \
		t_tokenizer *tokens, char *line)
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
				error_tokens(tokens, parse);
			str = tokens->line;
			if (!(tokens->line = ft_strjoin(str, tmp)))
				error_tokens(tokens, parse);
			free(str);
			free(tmp);
			return ;
		}
	}
	if (parse->type != 0 && tokens->tokens[tokens->tok_i][0] == '$')
		check_env_dollar1(parse, tokens, line);
}

void	sort_dollar1(t_minishell *mini, t_parser *parse, \
		t_tokenizer *tokens, char **cash)
{
	while (tokens->tokens[tokens->tok_i][++tokens->line_i] \
	&& (ft_isalpha(tokens->tokens[tokens->tok_i][tokens->line_i]) \
	|| ft_isdigit(tokens->tokens[tokens->tok_i][tokens->line_i]) \
	|| tokens->tokens[tokens->tok_i][tokens->line_i] == '_'))
	{
		if (!((*cash) = ft_charjoin(cash, \
		tokens->tokens[tokens->tok_i][tokens->line_i])))
			error_tokens(tokens, parse);
	}
	check_env_dollar(mini, parse, tokens, (*cash));
	--tokens->line_i;
}

void	sort_dollar(t_minishell *mini, t_parser *parse, t_tokenizer *tokens)
{
	char	*cash;

	if (!(cash = ft_strdup("")))
		error_tokens(tokens, parse);
	if (after_dollar_alone(mini, parse, tokens, &cash))
		;
	else if (ft_isalpha(tokens->tokens[tokens->tok_i][tokens->line_i + 1]) \
	|| tokens->tokens[tokens->tok_i][tokens->line_i + 1] == '_')
		sort_dollar1(mini, parse, tokens, &cash);
	else if (tokens->tokens[tokens->tok_i][tokens->line_i + 1] == 39 \
	|| tokens->tokens[tokens->tok_i][tokens->line_i + 1] == 34)
		;
	else
	{
		if (!(tokens->line = ft_charjoin(&tokens->line, \
		tokens->tokens[tokens->tok_i][tokens->line_i])))
			error_tokens(tokens, parse);
	}
	free(cash);
	cash = NULL;
}
