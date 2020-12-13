/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:17:35 by heusebio          #+#    #+#             */
/*   Updated: 2020/05/19 20:18:05 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str1;
	int		s1_len;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	s1_len = ft_strlen((char *)s1);
	while (s1 && ft_strrchr(set, s1[s1_len]) && s1_len)
		s1_len--;
	str1 = ft_substr((char*)s1, 0, s1_len + 1);
	return (str1);
}
