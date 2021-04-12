/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 12:23:03 by heusebio          #+#    #+#             */
/*   Updated: 2021/01/30 21:04:05 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		redir_utils(t_parser *pars, t_tokenizer *tokens)
{
	if (!pars->cmd)
	{
		if (!(pars->cmd = ft_strdup(tokens->tokens[tokens->tok_i])))
			error_tokens(tokens, pars);
	}
	else
	{
		if (!(pars->arg[pars->i_arg++] = \
		ft_strdup(tokens->tokens[tokens->tok_i])))
			error_tokens(tokens, pars);
	}
}
