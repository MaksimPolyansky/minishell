/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 21:15:14 by wphylici          #+#    #+#             */
/*   Updated: 2021/02/05 22:51:04 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_repeat(t_parser *data, int i)
{
	int		j;
	char	*tmp;

	j = 0;
	if (!(tmp = trim_str(data->arg[i])))
		my_exit(data, EXIT_FAILURE);
	while (j < g_in->i_env)
	{
		if (g_in->env[j])
			if (ft_strncmp(g_in->env[j], tmp, ft_strlen(tmp)) == 0)
				if (check(data, tmp, j))
					if (change_env(data, i, j))
					{
						free(tmp);
						return (-1);
					}
		j++;
	}
	free(tmp);
	return (0);
}

char	**alloc_new_env(t_parser *data, int j)
{
	int		i;
	int		l;
	char	**new;

	i = 0;
	l = 0;
	if (!(new = (char **)malloc(sizeof(char *) * (g_in->i_env + 1))))
		my_exit(data, EXIT_FAILURE);
	while (g_in->env[i])
	{
		if (!(new[i++] = ft_strdup(g_in->env[l++])))
			my_exit(data, EXIT_FAILURE);
	}
	if (!(new[i] = ft_strdup(data->arg[j])))
		my_exit(data, EXIT_FAILURE);
	new[++i] = NULL;
	free_double_array(g_in->env);
	return (new);
}

void	add_env(t_parser *data)
{
	int i;
	int i_tmp;

	i = 1;
	i_tmp = data->i_arg;
	while (i_tmp)
	{
		if (check_name(data, i))
			invalid_identifier(data, i);
		else if (!check_repeat(data, i))
		{
			if (!(g_in->env = alloc_new_env(data, i)))
				my_exit(data, EXIT_FAILURE);
			g_in->i_env++;
		}
		i++;
		i_tmp--;
	}
}

void	oldpwd_proc(int i)
{
	if (!g_in->flag && ft_strncmp(g_in->env[i], "OLDPWD=", 7) == 0)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd("OLDPWD\n", 1);
	}
}

int		cmd_export(t_parser *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (data->i_arg > 0)
		add_env(data);
	else
	{
		while (i < g_in->i_env)
		{
			if (g_in->env[i])
			{
				oldpwd_proc(i);
				output(i, j);
				j = 0;
			}
			i++;
		}
	}
	return (0);
}
