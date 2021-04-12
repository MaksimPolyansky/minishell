/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 00:35:05 by wphylici          #+#    #+#             */
/*   Updated: 2021/02/05 22:52:56 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env(int i)
{
	free(g_in->env[i]);
	g_in->env[i] = NULL;
	g_in->i_env--;
}

void	del_few_env(t_parser *data, int j)
{
	int		i;
	int		i_tmp;
	char	*tmp;

	i = 0;
	i_tmp = g_in->i_env - 1;
	while (i_tmp > 0)
	{
		if (g_in->env[i])
		{
			if (ft_strncmp(g_in->env[i], data->arg[j],
			ft_strlen(data->arg[j])) == 0)
			{
				if (!(tmp = trim_str(data->arg[j])))
					my_exit(data, EXIT_FAILURE);
				if (check(data, tmp, i))
				{
					free_env(i);
					free(tmp);
				}
			}
			i_tmp--;
		}
		i++;
	}
}

int		check_valid(t_parser *data, int i)
{
	int j;

	j = 1;
	if (data->arg[i][0] == '_' || (data->arg[i][0] >= 'A' &&
	data->arg[i][0] <= 'Z') || (data->arg[i][0] >= 'a' &&
	data->arg[i][0] <= 'z'))
	{
		while (data->arg[i][j] && data->arg[i][j] != '=')
		{
			if ((data->arg[i][j] >= '0' && data->arg[i][j] <= '9') ||
			data->arg[i][j] == '_' || (data->arg[i][j] >= 'A' &&
			data->arg[i][j] <= 'Z') || (data->arg[i][j] >= 'a'
			&& data->arg[i][j] <= 'z'))
				j++;
			else
				return (-1);
		}
	}
	else
		return (-1);
	return (0);
}
