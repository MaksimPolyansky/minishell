/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:36:25 by wphylici          #+#    #+#             */
/*   Updated: 2021/02/05 21:58:54 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fork_pipe(t_parser *parse)
{
	t_parser *tmp;

	ft_pipe(parse);
	tmp = parse->pipe;
	while (tmp->pipe)
	{
		ft_pipe(tmp);
		tmp = tmp->pipe;
	}
	command_output(tmp);
}

void	check_input(t_minishell *mini)
{
	t_tokenizer		tokens;
	t_parser		*parse;

	tokens_clear(&tokens);
	if (lexxer(mini, &tokens))
	{
		tokens.tok_i = -1;
		parse = parser(mini, &tokens);
		free_dline_tokens(&tokens);
		list_counter(parse);
		if (ft_strcmp(parse->cmd, "exit"))
			g_in->exec_stat = 0;
		if (parse->pipe)
			fork_pipe(parse);
		else
			command_output(parse);
		free_parse(parse);
		if (mini->input[mini->line_i])
			check_input(mini);
	}
}
