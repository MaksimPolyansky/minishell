/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 13:13:08 by heusebio          #+#    #+#             */
/*   Updated: 2020/05/20 10:41:06 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_n_len(int n)
{
	int n_len;

	n_len = 1;
	if (n < 0)
	{
		n_len++;
		n *= -1;
	}
	while (n / 10)
	{
		n_len++;
		n /= 10;
	}
	return (n_len);
}

static char	*ft_n_str(char *str, unsigned int num, int i, int n_len)
{
	unsigned int	k;
	unsigned int	n;

	k = 1;
	n = num;
	while (n / 10)
	{
		k *= 10;
		n /= 10;
	}
	while ((n_len - 1) > i)
	{
		str[++i] = num / k + '0';
		num %= k;
		k /= 10;
	}
	str[++i] = '\0';
	return (str);
}

char		*ft_itoa(int n)
{
	char			*str;
	unsigned int	num;
	int				i;
	int				n_len;

	n_len = ft_n_len(n);
	if (!(str = (char*)malloc(sizeof(char) * (n_len + 1))))
		return (NULL);
	i = -1;
	if (n < 0)
	{
		str[++i] = '-';
		num = n * (-1);
	}
	else
		num = n;
	return (ft_n_str(str, num, i, n_len));
}
