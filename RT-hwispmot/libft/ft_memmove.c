/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 15:39:04 by fwisp             #+#    #+#             */
/*   Updated: 2018/12/20 19:48:03 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char *src_tmp;
	char *dest_tmp;

	src_tmp = (char *)src;
	dest_tmp = (char *)dest;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	else
		while (n-- > 0)
			dest_tmp[n] = src_tmp[n];
	return (dest);
}
