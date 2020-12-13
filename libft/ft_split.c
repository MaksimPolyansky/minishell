/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 12:25:53 by heusebio          #+#    #+#             */
/*   Updated: 2020/05/24 20:46:54 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	how_many_string(char const *s, char c)
{
	int	point;
	int	i;

	point = 0;
	i = 0;
	if (*s == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			point++;
		}
	}
	return (point);
}

static char	*new_string(char const *s, char c)
{
	int		i;
	char	*str;
	int		n;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	n = 0;
	while (s[n] != c && s[n])
	{
		str[n] = s[n];
		n++;
	}
	str[n] = '\0';
	return (str);
}

static void	**my_free(char **str, int i)
{
	while (i > 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
	str = NULL;
	return (NULL);
}

char		**ft_split(char const *s, char c)
{
	char	**str;
	int		s_len;
	int		res;

	if (!s)
		return (NULL);
	if (!(str = (char**)malloc(sizeof(char*) * (how_many_string(s, c) + 1))))
		return (NULL);
	s_len = 0;
	res = 0;
	while (s[s_len] != '\0' && res < how_many_string(s, c))
	{
		while (s[s_len] == c)
			s_len++;
		if (!(str[res] = new_string(s + s_len, c)))
			return ((char**)my_free(str, res));
		while (s[s_len] != c && s[s_len])
			s_len++;
		res++;
	}
	str[res] = NULL;
	return (str);
}
