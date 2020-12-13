/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 13:21:52 by heusebio          #+#    #+#             */
/*   Updated: 2020/08/21 13:37:00 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str1;
	int		k;
	int		p;

	if (!s2)
		return (NULL);
	str1 = (char*)malloc(sizeof(char) * (ft_strlen((char *)s1) \
									+ ft_strlen((char *)s2) + 1));
	if (!str1)
		return (NULL);
	k = 0;
	while (s1[k] != '\0')
	{
		str1[k] = s1[k];
		k++;
	}
	p = 0;
	while (s2[p] != '\0')
	{
		str1[k + p] = s2[p];
		p++;
	}
	str1[k + p] = '\0';
	return (str1);
}
