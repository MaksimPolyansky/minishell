/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 11:34:29 by heusebio          #+#    #+#             */
/*   Updated: 2020/05/17 11:34:06 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*str;
	size_t	len;

	len = nmemb * size;
	str = (char*)malloc(len);
	if (!str)
		return (NULL);
	else
		ft_bzero(str, len);
	return (str);
}
