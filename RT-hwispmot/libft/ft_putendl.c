/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:05:21 by fwisp             #+#    #+#             */
/*   Updated: 2018/12/14 21:33:48 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl(char const *s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
		write(1, &s[i++], 1);
	write(1, "\n", 1);
}