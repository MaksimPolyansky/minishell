/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 18:13:34 by heusebio          #+#    #+#             */
/*   Updated: 2020/12/19 18:16:23 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_charjoin(char const *s1, char const s2)
{
	char	*str1;
	int		k;

	str1 = (char*)malloc(sizeof(char) * (ft_strlen((char *)s1) + 2));
	if (!str1)
		return (NULL);
	k = 0;
	while (s1[k] != '\0')
	{
		str1[k] = s1[k];
		k++;
	}
	str1[k++] = s2;
	str1[k] = '\0';
	return (str1);
}
