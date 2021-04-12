/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:44:51 by wphylici          #+#    #+#             */
/*   Updated: 2021/01/31 20:19:26 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_minishell		*g_in;

void	alloc_struct(t_parser *data, char **envp)
{
	int			i;

	i = -1;
	if (!(g_in = (t_minishell*)ft_calloc(sizeof(t_minishell), 1)))
		my_exit(data, EXIT_FAILURE);
	g_in->i_env = counter_dbl_arr(envp);
	if (!(g_in->env = (char**)ft_calloc((g_in->i_env), sizeof(char*))))
		my_exit(data, EXIT_FAILURE);
	while (envp[++i])
		if (!(g_in->env[i] = ft_strdup(envp[i])))
			my_exit(data, EXIT_FAILURE);
}

void	check_ctrl_d(void)
{
	if (g_in->flag_input == 21)
	{
		if (g_in->input)
			free(g_in->input);
		g_in->input = NULL;
		g_in->flag_input = 0;
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_parser	*data;

	data = NULL;
	if (**argv && argc)
		;
	alloc_struct(data, envp);
	while (1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
		ft_putstr_fd(ANSI_COLOR_CYAN"\e[1mminishell ➜  \e[1m"
		ANSI_COLOR_MAGENTA, 1);
		g_in->stdin = dup(0);
		g_in->stdout = dup(1);
		ft_putstr_fd(g_in->input, 1);
		get_next_line(0, &g_in->input);
		check_ctrl_d();
		if (!g_in->input)
			continue;
		ft_putstr_fd(ANSI_COLOR_RESET, 1);
		check_input(g_in);
		free_struct();
	}
	return (0);
}
