/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_home_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 02:52:44 by wphylici          #+#    #+#             */
/*   Updated: 2021/01/31 18:35:44 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	save_home_path(void)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (g_in->env[i])
	{
		if (ft_strncmp(g_in->env[i], "HOME=", 5) == 0)
		{
			if (ft_strcmp(g_in->env[i], "HOME=") == 0)
				;
			else
			{
				tmp = ft_strchr(g_in->env[i], '=');
				g_in->home_path = ft_strdup(++tmp);
			}
			break ;
		}
		i++;
	}
}
