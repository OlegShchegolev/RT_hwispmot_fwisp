/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 15:37:07 by fwisp             #+#    #+#             */
/*   Updated: 2018/12/14 15:37:13 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	size_t	i;
	char	*out;

	i = 0;
	if ((out = (char *)malloc(sizeof(char) * size)))
	{
		while (i < size)
			out[i++] = 0;
		return ((void *)out);
	}
	else
		return (NULL);
}
