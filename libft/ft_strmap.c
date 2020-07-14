/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 15:42:41 by fwisp             #+#    #+#             */
/*   Updated: 2018/12/17 20:44:59 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	len;
	size_t	i;
	char	*out;

	len = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	while (s[len] != '\0')
		len++;
	if (!(out = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		out[i] = f(s[i]);
		i++;
	}
	out[i] = '\0';
	return (out);
}
