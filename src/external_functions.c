/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvania <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 12:06:34 by lvania            #+#    #+#             */
/*   Updated: 2020/08/20 12:06:37 by lvania           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			get_object_parameters_inner(t_cl_object *object, char *str)
{
	if (ft_strstr(str, "center:"))
		object->center = parse_vector(ft_strstr(str, "center:"));
	if (ft_strstr(str, "direction:"))
		object->norm = norm_v(parse_vector(ft_strstr(str, "direction:")));
	if (ft_strstr(str, "color:"))
		object->color = parse_color(ft_strstr(str, "color:"));
	if (ft_strstr(str, "radius:"))
		object->radius = ft_atof(ft_strstr(str, "radius:") + 7);
}
