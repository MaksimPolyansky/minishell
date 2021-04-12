/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 02:53:58 by wphylici          #+#    #+#             */
/*   Updated: 2021/02/01 21:32:57 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (g_in->flag_input == 42)
			g_in->flag_input = 21;
		ft_putstr_fd("\b\b  \b\b", 1);
		ft_putstr_fd(ANSI_COLOR_CYAN"\n\e[1mminishell ➜  \e[1m"
		ANSI_COLOR_MAGENTA, 1);
		g_in->exec_stat = 1;
	}
	else if (sig == SIGQUIT)
		write(1, "\b\b  \b\b", 6);
}
