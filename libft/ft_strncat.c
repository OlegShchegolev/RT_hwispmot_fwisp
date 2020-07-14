/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 15:43:21 by fwisp             #+#    #+#             */
/*   Updated: 2018/12/14 15:43:22 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	const char	*tmp1;
	char		*tmp2;

	tmp1 = src;
	tmp2 = dest;
	while (*tmp2 != '\0')
		tmp2++;
	while (*tmp1 != '\0' && n-- > 0)
		*tmp2++ = *tmp1++;
	*tmp2 = '\0';
	return (dest);
}
