/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 22:32:23 by wphylici          #+#    #+#             */
/*   Updated: 2021/01/27 01:25:28 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_fork(pid_t pid)
{
	int		status;

	waitpid(pid, &status, WUNTRACED);
	g_in->exec_stat = WEXITSTATUS(status);
	if (g_in->fd[1] >= 3)
		close(g_in->fd[1]);
	dup2(g_in->fd[0], 0);
	if (g_in->fd[0] >= 3)
		close(g_in->fd[0]);
}

void	fork_error(t_parser *data)
{
	if (g_in->fd[1] >= 3)
		close(g_in->fd[1]);
	if (g_in->fd[0] >= 3)
		close(g_in->fd[0]);
	ft_putendl_fd("error: fatal", 2);
	my_exit(data, 1);
}

void	ft_pipe(t_parser *data)
{
	pid_t	pid;

	pipe(g_in->fd);
	pid = fork();
	if (pid == 0)
	{
		if (g_in->fd[0] >= 3)
			close(g_in->fd[0]);
		dup2(g_in->fd[1], 1);
		if (g_in->fd[1] >= 3)
			close(g_in->fd[1]);
		command_output(data);
		my_exit(data, 0);
	}
	else if (pid < 0)
		fork_error(data);
	else
		exit_fork(pid);
}
