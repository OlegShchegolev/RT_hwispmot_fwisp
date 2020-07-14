/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 15:40:16 by fwisp             #+#    #+#             */
/*   Updated: 2018/12/14 15:40:18 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	const char	*tmp1;
	const char	*tmp2;

	tmp1 = s1;
	tmp2 = s2;
	while (*tmp1 == *tmp2)
		if (*tmp1 == '\0')
			return (0);
		else
		{
			tmp1++;
			tmp2++;
		}
	return ((unsigned char)*tmp1 - (unsigned char)*tmp2);
}
