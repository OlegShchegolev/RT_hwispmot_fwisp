/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 15:45:40 by fwisp             #+#    #+#             */
/*   Updated: 2018/12/14 20:59:19 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**create_out(char const *s, char c)
{
	char	**out;
	size_t	i;
	size_t	count;

	i = 0;
	if (!s)
		return (NULL);
	if (s[i] != c)
		count = 1;
	else
		count = 0;
	while (s[++i] != '\0')
		if (s[i - 1] == c && s[i] != c)
			count++;
	if (!(out = (char **)malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	return (out);
}

static char	*get_word(char const *s, char c, int beg)
{
	char	*word;
	int		i;

	i = beg;
	while (s[i] != c && s[i] != '\0')
		i++;
	if (!(word = (char *)malloc(sizeof(char) * (i - beg + 1))))
		return (NULL);
	i = beg;
	while (s[i] != c && s[i] != '\0')
	{
		word[i - beg] = s[i];
		i++;
	}
	word[i - beg] = '\0';
	return (word);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**out;
	int		i;
	int		j;

	i = 0;
	if (!(out = create_out(s, c)))
		return (NULL);
	j = 0;
	while (s[i] != '\0')
		if (s[i] != c)
			if (!(out[j++] = get_word(s, c, i)))
			{
				while (--j >= 0)
					free(out[j]);
				free(out);
				return (NULL);
			}
			else
				while (s[i] != c && s[i] != '\0')
					i++;
		else
			i++;
	out[j] = NULL;
	return (out);
}
