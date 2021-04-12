/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 18:47:37 by wphylici          #+#    #+#             */
/*   Updated: 2021/01/31 19:27:24 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	output_env(int i)
{
	int j;

	j = 0;
	while (g_in->env[i][j])
	{
		if (g_in->env[i][j] == '\'' || g_in->env[i][j] == '\"')
			j++;
		else
			ft_putchar_fd(g_in->env[i][j++], 1);
	}
}

void	cmd_env(void)
{
	int i;

	i = 0;
	while (i < g_in->i_env)
	{
		if (g_in->env[i] && ft_strchr(g_in->env[i], '='))
		{
			if (!g_in->flag && ft_strncmp(g_in->env[i], "OLDPWD=", 7) == 0)
				i++;
			output_env(i);
			write(1, "\n", 1);
		}
		i++;
	}
}
