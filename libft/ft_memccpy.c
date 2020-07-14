/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 15:37:40 by fwisp             #+#    #+#             */
/*   Updated: 2018/12/14 16:09:17 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	const char	*tmp_in;
	char		*tmp_out;
	char		tmp_c;

	tmp_c = (char)c;
	tmp_in = (const char *)src;
	tmp_out = (char *)dest;
	while (n > 0)
		if (*tmp_in == tmp_c)
		{
			*tmp_out++ = *tmp_in++;
			break ;
		}
		else
		{
			*tmp_out++ = *tmp_in++;
			n--;
		}
	if (n == 0)
		return (NULL);
	else
		return ((void *)tmp_out);
}
