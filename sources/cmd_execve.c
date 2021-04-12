/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 02:29:46 by wphylici          #+#    #+#             */
/*   Updated: 2021/02/05 21:32:28 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		read_dir(t_parser *data, DIR *dir)
{
	int				len;
	struct dirent	*files;

	len = ft_strlen(data->cmd);
	while ((files = readdir(dir)) != NULL)
	{
		if (files->d_namlen == len && !ft_strcmp(files->d_name, data->cmd))
		{
			(void)closedir(dir);
			return (0);
		}
	}
	(void)closedir(dir);
	return (-1);
}

int		parser_for_cmd(t_parser *data)
{
	int		i;
	DIR		*dir;

	i = -1;
	if (init_cmd_path(data))
		return (-1);
	while (g_in->cmd_path[++i])
	{
		if (!(dir = opendir(g_in->cmd_path[i])))
		{
			free_double_array(g_in->cmd_path);
			return (-1);
		}
		if (!read_dir(data, dir))
			strjoin_cmd_path(data, i);
	}
	free_double_array(g_in->cmd_path);
	return (0);
}

void	exit_from_fork(pid_t pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, WUNTRACED);
	signal(SIGINT, sig_handler);
	signal(SIGINT, sig_handler);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
		{
			write(1, "\n", 1);
			g_in->exec_stat = 130;
		}
		else if (WTERMSIG(status) == 3)
		{
			write(1, "^\\Quit: 3\n", ft_strlen("^\\Quit: 3\n"));
			g_in->exec_stat = 131;
		}
	}
	else
		g_in->exec_stat = WEXITSTATUS(status);
}

void	fork_execve(t_parser *data)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		execve(data->cmd, data->arg, g_in->env);
	}
	else if (pid < 0)
	{
		if (g_in->fd[1] >= 3)
			close(g_in->fd[1]);
		if (g_in->fd[0] >= 3)
			close(g_in->fd[0]);
		ft_putendl_fd("error: fatal", 2);
		my_exit(data, 1);
	}
	else
		exit_from_fork(pid);
}

int		cmd_execve(t_parser *data)
{
	if (data->arg[0])
		free(data->arg[0]);
	if (!(data->arg[0] = ft_strdup(data->cmd)))
		my_exit(data, EXIT_FAILURE);
	if (parser_for_cmd(data) == -1)
		return (-1);
	if (!processing_error_cmd(data))
		fork_execve(data);
	return (0);
}
