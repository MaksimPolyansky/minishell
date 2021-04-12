/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 16:21:56 by wphylici          #+#    #+#             */
/*   Updated: 2021/01/27 03:57:32 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		writing_in_line(char **line, char *buf)
{
	char *tmp;

	tmp = *line;
	if (!(*line = ft_strjoin(tmp, buf)))
		exit(EXIT_FAILURE);
	my_free_gnl(&tmp, 0);
	return (0);
}

void	check_error(char *buf, int fd)
{
	if (read(fd, buf, 0) < 0)
		exit(EXIT_FAILURE);
}

int		get_line(int fd, char **line)
{
	char		buf[B_S + 1];
	char		*pointer_to_n;
	int			how_many_was_read;

	!(*line = ft_strdup("")) ? exit(EXIT_FAILURE) : 0;
	pointer_to_n = NULL;
	how_many_was_read = 0;
	check_error(buf, fd);
	while (!pointer_to_n && (how_many_was_read = read(fd, buf, B_S)) >= 0)
	{
		if (how_many_was_read == 0 && buf[0] != '\0')
		{
			ft_putstr_fd("  \b\b", 1);
			buf[1] = '\0';
			g_in->flag_input = 42;
			continue ;
		}
		else if (how_many_was_read == 0)
			exit_cntrl_d();
		buf[how_many_was_read] = '\0';
		if ((pointer_to_n = ft_strchr(buf, '\n')))
			*pointer_to_n = '\0';
		writing_in_line(line, buf);
	}
	return (how_many_was_read ? READ : 0);
}

int		get_next_line(int fd, char **line)
{
	int			res;

	res = 0;
	if (!line || fd < 0 || B_S < 1 || B_S > 2147483647)
		return (ERROR);
	if ((res = get_line(fd, line)) == -1)
		return (-1);
	return (res);
}
