/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 02:14:04 by wphylici          #+#    #+#             */
/*   Updated: 2021/01/28 01:54:26 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		not_one_red(t_parser *tmp)
{
	int	fd;

	fd = 0;
	if (stat(tmp->arg_red, g_in->buf) == -1)
	{
		if ((fd = open(tmp->arg_red, O_RDWR | O_CREAT,
		S_IWRITE | S_IREAD)) == -1)
			return (error_redir(tmp));
	}
	else if (tmp->type == 2)
		if ((fd = open(tmp->arg_red, O_RDWR | O_TRUNC)) == -1)
			return (error_redir(tmp));
	close(fd);
	return (0);
}

int		check_env_name(t_parser *tmp)
{
	if (tmp->fail == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tmp->arg_red, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		g_in->exec_stat = 1;
		return (-1);
	}
	return (0);
}

int		redirect(t_parser *data)
{
	t_parser	*tmp;

	if (!(g_in->buf = (struct stat *)malloc(sizeof(struct stat))))
		my_exit(data, EXIT_FAILURE);
	tmp = data->redir;
	while (tmp)
	{
		if (check_env_name(tmp))
			return (-1);
		else if (!tmp->redir)
		{
			if (tmp->type == 1)
				return (red_type_1(tmp));
			else if (tmp->type == 2)
				return (red_type_2(tmp));
			else if (tmp->type == 3)
				return (red_type_3(tmp));
		}
		else if (not_one_red(tmp))
			return (-1);
		tmp = tmp->redir;
	}
	return (0);
}
