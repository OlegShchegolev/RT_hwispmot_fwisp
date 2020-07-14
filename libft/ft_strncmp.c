/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 15:43:34 by fwisp             #+#    #+#             */
/*   Updated: 2018/12/14 16:02:14 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const char *tmp1;
	const char *tmp2;

	tmp1 = s1;
	tmp2 = s2;
	if (!n)
		return (0);
	while (*tmp1 == *tmp2 && n-- > 0)
		if (*tmp1 == '\0' || n == 0)
			return (0);
		else
		{
			tmp1++;
			tmp2++;
		}
	return ((unsigned char)*tmp1 - (unsigned char)*tmp2);
}
