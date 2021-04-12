/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 20:26:06 by wphylici          #+#    #+#             */
/*   Updated: 2021/02/01 21:44:34 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	uncorrect_path(char *arg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_in->exec_stat = 1;
}

int		check_availability(void)
{
	int i;

	i = 0;
	while (i < g_in->i_env)
	{
		if (g_in->env[i])
			if (ft_strncmp(g_in->env[i], "HOME=", 5) == 0)
				return (0);
		i++;
	}
	return (-1);
}

void	set_oldpwd(void)
{
	int		i;
	char	output[1001];

	i = -1;
	while (g_in->env[++i])
	{
		if (ft_strncmp(g_in->env[i], "OLDPWD=", 7) == 0 && g_in->flag)
		{
			ft_bzero(g_in->env[i], ft_strlen(g_in->env[i]));
			ft_strcpy(g_in->env[i], "OLDPWD=");
			ft_strcpy(ft_strchr(g_in->env[i], '\0'), getcwd(output, 1000));
			break ;
		}
	}
}

void	cmd_cd(t_parser *data)
{
	int i;

	i = 0;
	set_oldpwd();
	if (data->i_arg == 0)
	{
		if (check_availability())
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			g_in->exec_stat = 1;
			return ;
		}
		else if (!g_in->home_path)
			return ;
		else if (chdir(g_in->home_path) == -1)
			uncorrect_path(g_in->home_path);
		else
			g_in->flag = 1;
	}
	else if (chdir(data->arg[1]) == -1 && data->i_arg > 0)
		uncorrect_path(data->arg[1]);
	else
		g_in->flag = 1;
}
