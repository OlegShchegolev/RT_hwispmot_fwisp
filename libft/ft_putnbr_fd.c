/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:05:56 by fwisp             #+#    #+#             */
/*   Updated: 2018/12/14 16:07:44 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	int		sign;

	sign = 1;
	if (n < 0)
	{
		write(fd, "-", 1);
		sign = -1;
	}
	if (n / 10 == 0)
	{
		c = n * sign + 48;
		write(fd, &c, 1);
	}
	else
	{
		ft_putnbr_fd(sign * (n / 10), fd);
		ft_putnbr_fd(sign * (n % 10), fd);
	}
}
