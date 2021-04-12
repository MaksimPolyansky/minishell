/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 20:59:48 by wphylici          #+#    #+#             */
/*   Updated: 2021/02/01 16:50:53 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_arg(t_parser *data)
{
	int i;

	i = -1;
	while (data->arg[1][++i])
	{
		if ((data->arg[1][i] == '_' ||
		(data->arg[1][i] >= 'A' && data->arg[1][i] <= 'Z') ||
		(data->arg[1][i] >= 'a' && data->arg[1][i] <= 'z')) ||
		ft_atoi(data->arg[1]) == 0 || ft_atoi(data->arg[1]) == -1)
		{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(data->arg[1], 1);
			ft_putstr_fd(": numeric argument required\n", 2);
			ft_putstr_fd(ANSI_COLOR_RESET, 1);
			my_exit(data, 255);
		}
	}
	if (data->i_arg > 1)
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		g_in->exec_stat = 1;
		return (1);
	}
	return (0);
}

void	cmd_exit(t_parser *data)
{
	if (data->i_arg > 0)
	{
		if (!check_arg(data))
		{
			ft_putstr_fd(ANSI_COLOR_RESET, 1);
			ft_putstr_fd("exit\n", 1);
			my_exit(data, ft_atoi(data->arg[1]));
		}
	}
	else
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd(ANSI_COLOR_RESET, 1);
		my_exit(data, g_in->exec_stat);
	}
}
