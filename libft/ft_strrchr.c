/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 23:15:33 by heusebio          #+#    #+#             */
/*   Updated: 2020/05/16 21:39:01 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*s1;
	int		i;

	s1 = (char *)s;
	i = ft_strlen(s1);
	if (!c)
		return (s1 + i);
	while (i > 0)
	{
		i--;
		if (s1[i] == (char)c)
			return (s1 + i);
	}
	return (NULL);
}
