/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_output.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 18:01:30 by wphylici          #+#    #+#             */
/*   Updated: 2021/02/03 08:04:25 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	after_command_output(void)
{
	g_in->flag_execve = 0;
	if (g_in->buf)
		free(g_in->buf);
	g_in->buf = NULL;
	if (g_in->buf_exec)
		free(g_in->buf_exec);
	g_in->buf_exec = NULL;
	dup2(g_in->stdin, 0);
	dup2(g_in->stdout, 1);
}

void	command_output(t_parser *data)
{
	if (!redirect(data) && data->cmd)
	{
		save_home_path();
		if (ft_strcmp(data->cmd, "pwd") == 0 ||
		ft_strcmp(data->cmd, "PWD") == 0)
			cmd_pwd();
		else if (ft_strcmp(data->cmd, "echo") == 0 ||
		ft_strcmp(data->cmd, "ECHO") == 0)
			cmd_echo(data);
		else if (ft_strcmp(data->cmd, "cd") == 0 ||
		ft_strcmp(data->cmd, "CD") == 0)
			cmd_cd(data);
		else if (ft_strcmp(data->cmd, "env") == 0 ||
		ft_strcmp(data->cmd, "ENV") == 0)
			cmd_env();
		else if (ft_strcmp(data->cmd, "export") == 0)
			cmd_export(data);
		else if (ft_strcmp(data->cmd, "unset") == 0)
			cmd_unset(data);
		else if (ft_strcmp(data->cmd, "exit") == 0)
			cmd_exit(data);
		else
			cmd_execve(data);
	}
	after_command_output();
}
