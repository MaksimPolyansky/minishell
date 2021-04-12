/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 20:27:27 by wphylici          #+#    #+#             */
/*   Updated: 2021/01/31 18:41:31 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	output_echo(t_parser *data, int i)
{
	while (data->i_arg > i - 1)
	{
		ft_putstr_fd(data->arg[i], 1);
		if (data->i_arg > i)
			write(1, " ", 1);
		i++;
	}
}

void	cmd_echo(t_parser *data)
{
	int i;
	int flag;

	i = 1;
	flag = 0;
	if (data->arg[1])
	{
		if (ft_strcmp(data->arg[1], "-n") == 0)
		{
			flag = 1;
			i = 2;
		}
	}
	else
		write(1, "\n", 1);
	if (data->arg[i])
	{
		output_echo(data, i);
		if (!flag)
			write(1, "\n", 1);
	}
}
