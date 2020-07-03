/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 15:43:49 by fwisp             #+#    #+#             */
/*   Updated: 2018/12/17 21:16:09 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	const char	*tmp1;
	char		*tmp2;

	tmp1 = src;
	tmp2 = dest;
	while (n > 0 && *tmp1 != '\0')
	{
		*tmp2++ = *tmp1++;
		n--;
	}
	while (n-- > 0)
		*tmp2++ = '\0';
	return (dest);
}
