/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 00:05:25 by wphylici          #+#    #+#             */
/*   Updated: 2021/02/05 22:52:07 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		output(int i, int j)
{
	int flag;

	flag = 0;
	if (!g_in->flag && ft_strncmp(g_in->env[i], "OLDPWD=", 7) == 0)
		return (0);
	ft_putstr_fd("declare -x ", 1);
	if (ft_strchr(g_in->env[i], '"'))
		flag = 1;
	while (g_in->env[i][j])
	{
		if (g_in->env[i][j] == '=' && !flag)
		{
			ft_putchar_fd(g_in->env[i][j++], 1);
			write(1, "\"", 1);
		}
		if (g_in->env[i][j] == '\'')
			j++;
		else
			ft_putchar_fd(g_in->env[i][j++], 1);
	}
	if (ft_strchr(g_in->env[i], '=') && !flag)
		write(1, "\"", 1);
	write(1, "\n", 1);
	return (0);
}

int		check_name(t_parser *data, int i)
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

char	*trim_str(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!(tmp = (char *)malloc(sizeof(char))))
		return (NULL);
	if (ft_strchr(str, '=') || ft_strchr(str, '_'))
	{
		while (str[i])
		{
			if (str[i] == '=')
				break ;
			tmp[i] = str[i];
			i++;
		}
		tmp[i] = '\0';
	}
	else
		ft_strcpy(tmp, str);
	return (tmp);
}

int		change_env(t_parser *data, int i, int j)
{
	if (ft_strchr(data->arg[i], '"') || ft_strchr(data->arg[i], '=') ||
	ft_strchr(data->arg[i], '\''))
	{
		ft_bzero(g_in->env[j], ft_strlen(g_in->env[j]));
		ft_strcpy(g_in->env[j], data->arg[i]);
	}
	return (-1);
}

int		check(t_parser *data, char *arg, int j)
{
	char *tmp;

	if (!(tmp = trim_str(g_in->env[j])))
		my_exit(data, EXIT_FAILURE);
	if (ft_strcmp(tmp, arg) == 0)
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	return (0);
}
