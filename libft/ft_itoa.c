/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 15:47:57 by fwisp             #+#    #+#             */
/*   Updated: 2018/12/14 16:08:45 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*out;
	long	tmp;
	int		i;
	int		sign;

	i = 0;
	sign = 1;
	if (n < 0)
		sign = -1 + i++;
	tmp = (long)n * sign;
	while (tmp / 10 > 0 && ++i > 0)
		tmp /= 10;
	if (!(out = (char *)malloc(sizeof(char) * (++i + 1))))
		return (NULL);
	tmp = (long)n * sign;
	out[i--] = '\0';
	while (tmp / 10 > 0)
	{
		out[i--] = 48 + (tmp % 10);
		tmp /= 10;
	}
	out[i] = 48 + tmp;
	if (sign < 0)
		out[0] = '-';
	return (out);
}
