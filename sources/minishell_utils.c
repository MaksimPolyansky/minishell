/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:58:44 by wphylici          #+#    #+#             */
/*   Updated: 2021/02/03 08:09:11 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	my_exit(t_parser *data, int exit_status)
{
	free_parse(data);
	free_struct();
	free_double_array(g_in->env);
	after_command_output();
	if (g_in->fd[1] >= 3)
		close(g_in->fd[1]);
	if (g_in->fd[0] >= 3)
		close(g_in->fd[0]);
	free(g_in);
	exit(exit_status);
}

void	str_free(char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
}

void	list_counter(t_parser *data)
{
	t_parser *tmp;

	tmp = data->pipe;
	while (tmp != NULL)
	{
		g_in->count_list++;
		tmp = tmp->pipe;
	}
}

void	free_double_array(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	if (arr)
		free(arr);
	arr = NULL;
}
