/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execve_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 02:56:17 by wphylici          #+#    #+#             */
/*   Updated: 2021/02/01 21:44:13 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	strjoin_cmd_path(t_parser *data, int i)
{
	char	*tmp;
	char	*tmp_1;

	tmp = g_in->cmd_path[i];
	if (!(g_in->cmd_path[i] = ft_strjoin(tmp, "/")))
		my_exit(data, -1);
	free(tmp);
	tmp_1 = data->cmd;
	if (!(data->cmd = ft_strjoin(g_in->cmd_path[i], tmp_1)))
		my_exit(data, -1);
	free(tmp_1);
}

int		init_cmd_path(t_parser *data)
{
	int		i;

	i = 0;
	while (i < g_in->i_env)
	{
		if (g_in->env[i])
		{
			if (ft_strncmp(g_in->env[i], "PATH=", 5) == 0)
			{
				g_in->cmd_path = ft_split(ft_strchr(g_in->env[i], '/'), ':');
				return (0);
			}
		}
		i++;
	}
	return (no_such_file_cmd(data));
}
