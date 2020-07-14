/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 15:28:11 by fwisp             #+#    #+#             */
/*   Updated: 2018/12/20 19:35:39 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	const char	*tmp;
	int			sign;
	long		out;

	tmp = nptr;
	out = 0;
	sign = 1;
	while (*tmp == '\f' || *tmp == ' ' || *tmp == '\n' || \
		*tmp == '\t' || *tmp == '\v' || *tmp == '\r')
		tmp++;
	if (*tmp == '+' || *tmp == '-')
		if (*tmp++ == '-')
			sign = -1;
	while (*tmp >= '0' && *tmp <= '9')
		if ((out * 10 / 10 != out || out * 10 + (*tmp - 48) < 0) \
				&& sign == 1)
			return (-1);
		else if ((out * 10 / 10 != out || out * 10 + (*tmp - 48) < 0) \
				&& sign == -1)
			return (0);
		else
			out = out * 10 + (*tmp++ - 48);
	return ((int)out * sign);
}
