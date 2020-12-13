/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 15:05:33 by heusebio          #+#    #+#             */
/*   Updated: 2020/05/15 20:14:59 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	k;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] != '\0' && i != len)
	{
		if (big[i] == little[0])
		{
			k = 0;
			while (big[i] == little[k] && big[i] != '\0' && i != len)
			{
				i++;
				k++;
			}
			if (little[k] == '\0')
				return ((char *)&big[i - k]);
		}
		else
			i++;
	}
	return (NULL);
}
