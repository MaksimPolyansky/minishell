/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 10:57:26 by heusebio          #+#    #+#             */
/*   Updated: 2020/05/27 11:34:49 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst1;
	t_list	*lst2;

	if (!lst || !f)
		return (NULL);
	lst2 = NULL;
	while (lst)
	{
		lst1 = ft_lstnew(f(lst->content));
		if (!lst1)
		{
			ft_lstclear(&lst2, del);
			return (NULL);
		}
		ft_lstadd_back(&lst2, lst1);
		lst = lst->next;
	}
	return (lst2);
}
