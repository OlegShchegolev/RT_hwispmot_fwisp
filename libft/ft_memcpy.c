/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 15:38:34 by fwisp             #+#    #+#             */
/*   Updated: 2018/12/17 21:31:05 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*tmp_in;
	char		*tmp_out;

	if (dest == NULL && src == NULL)
		return (NULL);
	tmp_in = (const char *)src;
	tmp_out = (char *)dest;
	while (n-- > 0)
		*tmp_out++ = *tmp_in++;
	return (dest);
}
