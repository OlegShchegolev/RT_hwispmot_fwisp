/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 15:45:09 by fwisp             #+#    #+#             */
/*   Updated: 2018/12/14 15:53:57 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*out;
	size_t	beg;
	size_t	end;
	size_t	i;

	if (!s)
		return (NULL);
	beg = 0;
	while (s[beg] == ' ' || s[beg] == '\t' || s[beg] == '\n')
		beg++;
	if ((end = ft_strlen(s)) > 0)
		if (end > beg)
			while (s[end - 1] == ' ' || s[end - 1] == '\t' || \
					s[end - 1] == '\n')
				end--;
	if (!(out = (char *)malloc(sizeof(char) * (end - beg + 1))))
		return (NULL);
	i = 0;
	while (i < end - beg)
	{
		out[i] = s[beg + i];
		i++;
	}
	out[i] = '\0';
	return (out);
}
