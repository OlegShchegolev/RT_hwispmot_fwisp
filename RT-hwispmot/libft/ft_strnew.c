/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 15:44:30 by fwisp             #+#    #+#             */
/*   Updated: 2018/12/20 19:49:29 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*out;

	i = 0;
	if (size == (size_t)(-1))
		return (NULL);
	if (!(out = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (i <= size)
		out[i++] = '\0';
	return (out);
}
