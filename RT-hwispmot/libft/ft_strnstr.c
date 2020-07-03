/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:00:46 by fwisp             #+#    #+#             */
/*   Updated: 2018/12/14 20:50:53 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *ndl, size_t n)
{
	size_t			i;
	size_t			j;
	size_t			out;

	i = 0;
	j = 0;
	while (src[i + j] != '\0' && ndl[j] != '\0' && i + j < n)
	{
		if (src[i + j] != ndl[j])
		{
			out = i++;
			j = 0;
		}
		else
		{
			j++;
			if (j == ft_strlen(ndl))
				return ((char *)src + i);
		}
	}
	if (ft_strlen(ndl) == 0)
		return ((char *)src);
	return (NULL);
}
