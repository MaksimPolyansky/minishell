/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 11:19:31 by heusebio          #+#    #+#             */
/*   Updated: 2020/08/21 13:37:59 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		n;
	char	*dst;

	if (!(dst = (char*)malloc(sizeof(char) * (ft_strlen((char *)s) + 1))))
		return (NULL);
	n = 0;
	while (s[n] != '\0')
	{
		dst[n] = s[n];
		n++;
	}
	dst[n] = '\0';
	return (dst);
}
