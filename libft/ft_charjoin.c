/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 18:13:34 by heusebio          #+#    #+#             */
/*   Updated: 2021/01/10 18:47:44 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_charjoin(char **s1, char const s2)
{
	char	*str1;
	int		k;

	str1 = (char*)malloc(sizeof(char) * (ft_strlen(*s1) + 1) + 1);
	if (!str1)
		return (NULL);
	k = 0;
	while ((*s1)[k] != '\0')
	{
		str1[k] = (*s1)[k];
		k++;
	}
	str1[k++] = s2;
	str1[k] = '\0';
	free(*s1);
	return (str1);
}
