/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_type_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:48:10 by wphylici          #+#    #+#             */
/*   Updated: 2021/01/27 01:25:30 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		red_type_1(t_parser *tmp)
{
	int	fd;

	if ((fd = open(tmp->arg_red, O_RDONLY, S_IREAD)) == -1)
		return (error_redir(tmp));
	dup2(fd, 0);
	if (fd >= 3)
		close(fd);
	return (0);
}

int		red_type_2(t_parser *tmp)
{
	int	fd;

	if (stat(tmp->arg_red, g_in->buf) == -1)
	{
		if ((fd = open(tmp->arg_red, O_RDWR | O_CREAT,
		S_IWRITE | S_IREAD)) == -1)
			return (error_redir(tmp));
		dup2(fd, 1);
		if (fd >= 3)
			close(fd);
	}
	else
	{
		if ((fd = open(tmp->arg_red, O_RDWR | O_TRUNC)) == -1)
			return (error_redir(tmp));
		dup2(fd, 1);
		if (fd >= 3)
			close(fd);
	}
	return (0);
}

int		red_type_3(t_parser *tmp)
{
	int	fd;

	if (stat(tmp->arg_red, g_in->buf) == -1)
	{
		if ((fd = open(tmp->arg_red, O_RDWR | O_CREAT,
		S_IWRITE | S_IREAD)) == -1)
			return (error_redir(tmp));
		dup2(fd, 1);
		if (fd >= 3)
			close(fd);
	}
	else
	{
		if ((fd = open(tmp->arg_red, O_RDWR | O_APPEND)) == -1)
			return (error_redir(tmp));
		dup2(fd, 1);
		if (fd >= 3)
			close(fd);
	}
	return (0);
}
