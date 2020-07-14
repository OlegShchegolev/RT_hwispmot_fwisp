/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 15:49:12 by fwisp             #+#    #+#             */
/*   Updated: 2018/12/20 20:12:57 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_del(void *ptr, size_t n)
{
	if (ptr != NULL && n)
	{
		ft_memset(ptr, 0, n);
		ft_memdel(ptr);
	}
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*out;
	t_list	*tmp;

	if (!lst || !f)
		return (NULL);
	if (!(out = f(lst)))
		return (NULL);
	tmp = out;
	lst = lst->next;
	while (lst != NULL)
	{
		if (!(tmp->next = f(lst)))
		{
			ft_lstdel(&out, &ft_del);
			return (NULL);
		}
		lst = lst->next;
		tmp = tmp->next;
	}
	return (out);
}
