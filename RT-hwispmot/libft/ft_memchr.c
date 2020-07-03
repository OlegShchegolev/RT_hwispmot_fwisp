/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 15:37:58 by fwisp             #+#    #+#             */
/*   Updated: 2018/12/14 15:38:02 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char *tmp;

	tmp = (const char *)s;
	while (n--)
		if (*tmp++ == (char)c)
			return ((void *)(--tmp));
	return (NULL);
}
