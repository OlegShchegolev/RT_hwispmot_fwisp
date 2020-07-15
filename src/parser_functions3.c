/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_functions3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 02:42:55 by fwisp             #+#    #+#             */
/*   Updated: 2020/07/15 03:15:14 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			get_object_parameters(t_cl_object *object, char *str)
{
	if (ft_strstr(str, "center:"))
			object->center = parse_vector(ft_strstr(str, "center:"));
	if (ft_strstr(str, "direction:"))
			object->norm = parse_vector(ft_strstr(str, "direction:"));
	if (ft_strstr(str, "color:"))
			object->color = parse_color(ft_strstr(str, "color:"));
	if (ft_strstr(str, "radius:"))
			object->radius = ft_atof(ft_strstr(str, "radius:") + 7);
	if (ft_strstr(str, "alpha:"))
			object->alpha = ft_atof(ft_strstr(str, "alpha:") + 6);
	if (ft_strstr(str, "specular:"))
			object->specular = ft_atoi(ft_strstr(str, "specular:") + 9);
	if (ft_strstr(str, "reflective:"))
			object->reflective = ft_atof(ft_strstr(str, "reflective:") + 11);
	if (ft_strstr(str, "tex_num:"))
			object->texture = ft_atoi(ft_strstr(str, "tex_num:") + 8);
	if (ft_strstr(str, "tex_type:"))
			object->textype = parse_type(ft_strstr(str, "tex_type:") + 9);
	if (ft_strstr(str, "shift:"))
			object->shift = parse_2dvector(ft_strstr(str, "shift:") + 6);
	if (ft_strstr(str, "scale:"))
			object->scale = parse_2dvector(ft_strstr(str, "scale:") + 6);
	get_slices(object, str);
	if (ft_strstr(str, "negative:"))
			object->negative = ft_atoi(ft_strstr(str, "negative:") + 9);
}

char			parse_object_type(char *str)
{
	if (ft_strstr(str, "plane"))
		return 'p';
	if (ft_strstr(str, "sphere"))
		return 's';
	if (ft_strstr(str, "cyl"))
		return 'c';
	if (ft_strstr(str, "cone"))
		return 't';
	return 'n';
}

void	check_sources(t_cl_source *sources)
{
	float	sum;
    int     i;

	sum = 0.;
    i = -1;
	while (++i < N_SRC)
		sum += sources[i].intensity;
    i = -1;
	while (++i < N_SRC)
		sources[i].intensity /= sum;
}