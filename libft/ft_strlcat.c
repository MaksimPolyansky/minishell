/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 10:44:08 by heusebio          #+#    #+#             */
/*   Updated: 2020/05/17 19:32:23 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	n;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen((char *)src);
	if (size <= dst_len)
		return (src_len + size);
	i = 0;
	while (dst[i] != '\0')
		i++;
	n = 0;
	while (src[n] != '\0' && i < (size - 1))
	{
		dst[i] = src[n];
		i++;
		n++;
	}
	dst[i] = '\0';
	return (dst_len + src_len);
}
