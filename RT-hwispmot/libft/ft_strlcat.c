/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 15:42:07 by fwisp             #+#    #+#             */
/*   Updated: 2018/12/14 16:03:10 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t		n;
	size_t		out;

	out = ft_strlen((const char *)dest);
	if (size > out)
	{
		n = size - out - 1;
		dest = ft_strncat(dest, src, n);
		out += ft_strlen(src);
	}
	else
		out = size + ft_strlen(src);
	return (out);
}
