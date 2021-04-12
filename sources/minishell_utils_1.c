/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:45:36 by wphylici          #+#    #+#             */
/*   Updated: 2021/01/31 20:19:18 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int		counter_dbl_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i + 1);
}

void	free_struct(void)
{
	if (g_in->home_path)
		free(g_in->home_path);
	g_in->home_path = NULL;
	if (g_in->input)
		free(g_in->input);
	g_in->input = NULL;
	g_in->line_i = 0;
	close(g_in->stdin);
	close(g_in->stdout);
}
