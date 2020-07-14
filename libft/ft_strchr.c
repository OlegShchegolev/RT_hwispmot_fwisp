/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 15:39:54 by fwisp             #+#    #+#             */
/*   Updated: 2018/12/14 16:03:52 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char *tmp;

	tmp = (char *)s;
	while (*tmp != '\0' || *tmp == (char)c)
		if (*tmp == (char)c)
			return (tmp);
		else
			tmp++;
	return (NULL);
}
