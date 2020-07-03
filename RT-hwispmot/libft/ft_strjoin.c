/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 15:41:50 by fwisp             #+#    #+#             */
/*   Updated: 2018/12/14 15:41:53 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*out;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1) + ft_strlen(s2);
	if (!(out = (char *)malloc(sizeof(char) * (len1 + 1))))
		return (NULL);
	len1 = 0;
	len2 = 0;
	while (s1[len1] != '\0')
	{
		out[len1] = s1[len1];
		len1++;
	}
	while (s2[len2] != '\0')
	{
		out[len1 + len2] = s2[len2];
		len2++;
	}
	out[len1 + len2] = '\0';
	return (out);
}
