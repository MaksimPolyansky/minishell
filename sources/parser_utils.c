/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 11:18:32 by heusebio          #+#    #+#             */
/*   Updated: 2021/02/01 18:06:14 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			free_line_tokens(t_tokenizer *tokens)
{
	if (tokens->line)
		free(tokens->line);
	tokens->line = NULL;
	return (0);
}

int			free_dline_tokens(t_tokenizer *tokens)
{
	int		i;

	if (tokens->tokens)
	{
		i = 0;
		while (tokens->tokens[i])
		{
			free(tokens->tokens[i]);
			tokens->tokens[i++] = NULL;
		}
		free(tokens->tokens);
	}
	tokens->tokens = NULL;
	return (0);
}

void		free_parse(t_parser *parse)
{
	if (parse->cmd)
		free(parse->cmd);
	parse->cmd = NULL;
	if (g_in->home_path)
		free(g_in->home_path);
	g_in->home_path = NULL;
	if (parse->arg_red)
		free(parse->arg_red);
	parse->arg_red = NULL;
	free_dline_parse(parse);
	if (parse->pipe)
		free_parse(parse->pipe);
	if (parse->redir)
		free_parse(parse->redir);
	free(parse);
	parse = NULL;
}

int			check_sem(t_tokenizer *tokens)
{
	if (tokens->tokens[tokens->tok_i] \
	&& tokens->tokens[tokens->tok_i][0] == ';' \
	&& tokens->tokens[tokens->tok_i][1] == '\0')
		return (1);
	return (0);
}

t_parser	*check_pipe(t_minishell *mini, t_tokenizer *tokens)
{
	t_parser	*parse;

	if (tokens->tokens[tokens->tok_i] \
	&& tokens->tokens[tokens->tok_i][0] == '|' \
	&& tokens->tokens[tokens->tok_i][1] == '\0')
	{
		parse = parser(mini, tokens);
		return (parse);
	}
	return (NULL);
}
