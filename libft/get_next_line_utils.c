/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 02:33:09 by wphylici          #+#    #+#             */
/*   Updated: 2021/01/27 02:44:22 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		my_free_gnl(char **s, int ret_value)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
	return (ret_value);
}

void	exit_cntrl_d(void)
{
	write(1, "exit\n", 5);
	ft_putstr_fd("  \b\b", 1);
	ft_putstr_fd(ANSI_COLOR_RESET, 1);
	exit(g_in->exec_stat);
}
