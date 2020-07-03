/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpuntil.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 21:09:39 by fwisp             #+#    #+#             */
/*   Updated: 2018/12/20 19:50:47 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpuntil(char *s, char c)
{
	char		*out;
	size_t		len;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len] != '\0' || s[len] != c)
		len++;
	if (!(out = (char *)malloc(sizeof(char) * (len + 1))))
		return (ft_strncpy(out, s, len));
	else
		return (NULL);
}
