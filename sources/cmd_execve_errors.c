/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execve_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 02:31:06 by wphylici          #+#    #+#             */
/*   Updated: 2021/01/28 01:23:39 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		cmd_not_found_cmd(t_parser *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(data->cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_in->exec_stat = 127;
	return (-1);
}

int		no_such_file_cmd(t_parser *data)
{
	if (g_in->fd[1] >= 3)
		close(g_in->fd[1]);
	if (g_in->fd[0] >= 3)
		close(g_in->fd[0]);
	dup2(g_in->stdin, 0);
	dup2(g_in->stdout, 1);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(data->cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_in->exec_stat = 127;
	return (-1);
}

int		is_a_directory_cmd(t_parser *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(data->cmd, 2);
	ft_putstr_fd(": is a directory\n", 2);
	g_in->exec_stat = 126;
	return (-1);
}

int		permission_denied_cmd(t_parser *data)
{
	if (g_in->fd[1] >= 3)
		close(g_in->fd[1]);
	if (g_in->fd[0] >= 3)
		close(g_in->fd[0]);
	dup2(g_in->stdin, 0);
	dup2(g_in->stdout, 1);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(data->cmd, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	g_in->exec_stat = 126;
	return (-1);
}

int		processing_error_cmd(t_parser *data)
{
	if (!(g_in->buf_exec = (struct stat *)malloc(sizeof(struct stat))))
		my_exit(data, EXIT_FAILURE);
	if (stat(data->cmd, g_in->buf_exec) == -1 && ft_strchr(data->cmd, '/'))
		return (no_such_file_cmd(data));
	else if (!ft_strchr(data->cmd, '/'))
		return (cmd_not_found_cmd(data));
	else if (stat(data->cmd, g_in->buf_exec) != -1 &&
	g_in->buf_exec->st_mode & S_IFDIR)
		return (is_a_directory_cmd(data));
	else if (!(g_in->buf_exec->st_mode & S_IXUSR))
		return (permission_denied_cmd(data));
	return (0);
}
