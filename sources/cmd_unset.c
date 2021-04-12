/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 18:01:04 by wphylici          #+#    #+#             */
/*   Updated: 2021/01/29 03:19:55 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	invalid_identifier(t_parser *data, int i)
{
	ft_putstr_fd("minishell: export: ", 2);
	write(1, "`", 1);
	ft_putstr_fd(data->arg[i], 1);
	write(1, "'", 1);
	ft_putstr_fd(": not a valid identifier\n", 2);
	g_in->exec_stat = 1;
}

void	cycle_arg(t_parser *data)
{
	int j;

	j = 1;
	while (data->arg[j])
	{
		if (!check_valid(data, j))
		{
			del_few_env(data, j);
			j++;
		}
		else
			invalid_identifier(data, j++);
	}
}

int		del_one_by_one(t_parser *data, int i)
{
	if (ft_strncmp(g_in->env[i], data->arg[1], ft_strlen(data->arg[1])) == 0)
	{
		free(g_in->env[i]);
		g_in->env[i] = NULL;
		g_in->i_env--;
		return (1);
	}
	return (0);
}

void	glue_equal_sign(t_parser *data)
{
	char *tmp;

	tmp = data->arg[1];
	data->arg[1] = ft_strjoin(tmp, "=");
	free(tmp);
}

void	cmd_unset(t_parser *data)
{
	int i_tmp;
	int i;

	i = 0;
	i_tmp = g_in->i_env;
	if (data->i_arg == 1)
	{
		if (!check_valid(data, 1))
		{
			glue_equal_sign(data);
			while (i_tmp - 1)
			{
				if (g_in->env[i])
					if (del_one_by_one(data, i))
						break ;
				i++;
				i_tmp--;
			}
		}
		else
			invalid_identifier(data, 1);
	}
	if (data->i_arg > 1)
		cycle_arg(data);
}
