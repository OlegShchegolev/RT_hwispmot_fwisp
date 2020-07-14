/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 15:40:58 by fwisp             #+#    #+#             */
/*   Updated: 2018/12/14 16:07:21 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char *out;
	char *tmp;

	if (!(out = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	tmp = out;
	while (*s != '\0')
		*tmp++ = *s++;
	*tmp = '\0';
	return (out);
}
