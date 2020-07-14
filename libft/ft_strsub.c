/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 15:46:19 by fwisp             #+#    #+#             */
/*   Updated: 2018/12/14 15:56:03 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*out;
	char	*tmp;
	size_t	i;

	if (!s || !(out = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	tmp = out;
	i = 0;
	while (s[i] != '\0')
		if (start > 0)
		{
			i++;
			start--;
		}
		else if (len > 0)
		{
			len--;
			*tmp++ = s[i++];
		}
		else
			break ;
	if (start > 0 || len > 0)
		return (NULL);
	*tmp = '\0';
	return (out);
}
