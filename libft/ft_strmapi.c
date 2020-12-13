/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 22:36:27 by heusebio          #+#    #+#             */
/*   Updated: 2020/05/17 20:09:10 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str1;
	unsigned int	i;

	if (!f || !s)
		return (NULL);
	str1 = (char*)malloc(sizeof(char) * (ft_strlen((char *)s) + 1));
	if (!str1)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str1[i] = f(i, s[i]);
		i++;
	}
	str1[i] = '\0';
	return (str1);
}
