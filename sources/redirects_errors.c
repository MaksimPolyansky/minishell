/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 02:12:48 by wphylici          #+#    #+#             */
/*   Updated: 2021/01/27 01:25:33 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		error_redir(t_parser *tmp)
{
	if (g_in->fd[1] >= 3)
		close(g_in->fd[1]);
	if (g_in->fd[0] >= 3)
		close(g_in->fd[0]);
	dup2(g_in->stdin, 0);
	dup2(g_in->stdout, 1);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(tmp->arg_red, 2);
	write(1, ": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	write(1, "\n", 1);
	g_in->exec_stat = 1;
	return (-1);
}
