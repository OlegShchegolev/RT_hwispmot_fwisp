/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shchegolev <shchegolev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 22:44:08 by fwisp             #+#    #+#             */
/*   Updated: 2020/07/15 01:18:29 by shchegolev       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

cl_float3		return_zero_vector(void)
{
	cl_float3	zero;

	zero.s[0] = 0;
	zero.s[1] = 0;
	zero.s[2] = 0;
	return (zero);
}

cl_float2		return_zero_2dvector(void)
{
	cl_float2	zero;

	zero.s[0] = 0;
	zero.s[1] = 0;
	return (zero);
}

cl_float4		return_zero_4dvector(void)
{
	cl_float4	zero;

	zero.s[0] = 0;
	zero.s[1] = 0;
	zero.s[2] = 0;
	zero.s[3] = 0;
	return (zero);
}

cl_int3 		return_zero_color(void)
{
	cl_int3		zero;

	zero.s[0] = 0;
	zero.s[1] = 0;
	zero.s[2] = 0;
	return (zero);
}

cl_float3		parse_vector(char *str)
{
	cl_float3	v;

	if (!ft_strchr(str, '('))
		return (return_zero_vector());
	str = ft_strchr(str, '(') + 1;
	v.s[0] = ft_atof(str);
	if (!ft_strchr(str, ','))
		return (return_zero_vector());
	str = ft_strchr(str, ',') + 1;
	v.s[1] = ft_atof(str);
	if (!ft_strchr(str, ','))
		return (return_zero_vector());
	str = ft_strchr(str, ',') + 1;
	v.s[2] = ft_atof(str);
	if (!ft_strchr(str, ')'))
		return (return_zero_vector());
	return (v);
}

cl_float2		parse_2dvector(char *str)
{
	cl_float2	v;

	if (!ft_strchr(str, '('))
		return (return_zero_2dvector());
	str = ft_strchr(str, '(') + 1;
	v.s[0] = ft_atof(str);
	if (!ft_strchr(str, ','))
		return (return_zero_2dvector());
	str = ft_strchr(str, ',') + 1;
	v.s[1] = ft_atof(str);
	if (!ft_strchr(str, ')'))
		return (return_zero_2dvector());
	return (v);
}

cl_float4		parse_4dvector(char *str)
{
	cl_float4	v;

	if (!ft_strchr(str, '('))
		return (return_zero_4dvector());
	str = ft_strchr(str, '(') + 1;
	v.s[0] = ft_atof(str);
	if (!ft_strchr(str, ','))
		return (return_zero_4dvector());
	str = ft_strchr(str, ',') + 1;
	v.s[1] = ft_atof(str);
	if (!ft_strchr(str, ','))
		return (return_zero_4dvector());
	str = ft_strchr(str, ',') + 1;
	v.s[2] = ft_atof(str);
	if (!ft_strchr(str, ','))
		return (return_zero_4dvector());
	str = ft_strchr(str, ',') + 1;
	v.s[3] = ft_atof(str);
	if (!ft_strchr(str, ')'))
		return (return_zero_4dvector());
	return (v);
}

cl_int3		    parse_color(char *str)
{
	cl_int3		color;

	color = return_zero_color();
	if (!str)
		return (color);
	if (!ft_strchr(str, '('))
		return (color);
	str = ft_strchr(str, '(') + 1;
	color.s[0] = ft_atoi(str);
	if (!ft_strchr(str, ','))
		return (color);
	str = ft_strchr(str, ',') + 1;
	color.s[1] = ft_atoi(str);
	if (!ft_strchr(str, ','))
		return (color);
	color.s[2] = ft_atoi(ft_strchr(str, ',') + 1);
	return (color);
}

char			parse_type(char *str)
{
	while (*str == ' ' || *str == '\n')
		str++;
	return *str;
}

void			get_slices(t_cl_object *object, char *str0)
{
	int	i;
	char	*str;

	str = str0;
	i = -1;
	while (++i < 4 && ft_strstr(str, "slice:"))
	{
		str = ft_strstr(str, "slice:") + 6;
		object->slice[i] = parse_4dvector(str);
	}
	str = str0;
	i = -1;
	while (++i < 4 && ft_strstr(str, "slice_side:"))
	{
		str = ft_strstr(str, "slice_side:") + 11;
		object->slice_side[i] = ft_atoi(str);
	}
}

void			get_object_parameters(t_cl_object *object, char *str)
{
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

void			parse_plane(t_cl_object *objects, char *str, int *n)
{
	while (ft_strstr(str, "plane:") && *n < 20)
	{
		str = ft_strstr(str, "plane:") + ft_strlen("plane:");
		if (!ft_strstr(str, "center:") || !ft_strstr(str, "norm:"))
			return ;
		objects[*n].type = 'p';
		objects[*n].center = parse_vector(ft_strstr(str, "center:"));
		objects[*n].norm = parse_vector(ft_strstr(str, "norm:"));
		objects[*n].color = parse_color(ft_strstr(str, "color:"));
		get_object_parameters(&(objects[*n]), str);
        ++(*n);
	}
}

void			parse_sphere(t_cl_object *objects, char *str, int *n)
{
	while (ft_strstr(str, "sphere:") && *n < 20)
	{
		str = ft_strstr(str, "sphere:") + ft_strlen("sphere:");
		if (!ft_strstr(str, "center:") || !ft_strstr(str, "radius:"))
			return ;
		objects[*n].type = 's';
		objects[*n].center = parse_vector(ft_strstr(str, "center:"));
		objects[*n].radius = ft_atof(ft_strstr(str, "radius:") + \
													ft_strlen("radius:"));
		objects[*n].color = parse_color(ft_strstr(str, "color:"));
		get_object_parameters(&(objects[*n]), str);
        ++(*n);
	}
}

void			parse_cylinder(t_cl_object *objects, char *str, int *n)
{
	while (ft_strstr(str, "cyl:") && *n < N_OBJ)
	{
		str = ft_strstr(str, "cyl:") + ft_strlen("cyl:");
		if (!ft_strstr(str, "direction") || !ft_strstr(str, "center") || \
						!ft_strstr(str, "radius:"))
			return ;
		objects[*n].type = 'c';
		objects[*n].center = parse_vector(ft_strstr(str, "center:"));
		objects[*n].radius = ft_atof(ft_strstr(str, "radius:") + 7);
        objects[*n].norm = parse_vector(ft_strstr(str, "direction:"));
		objects[*n].color = parse_color(ft_strstr(str, "color:"));
		get_object_parameters(&(objects[*n]), str);
        ++n;
	}
}

void			parse_cone(t_cl_object *objects, char *str, int *n)
{
	while (ft_strstr(str, "cone:") && *n < N_OBJ)
	{
		str = ft_strstr(str, "cone:") + ft_strlen("cone:");
		if (!ft_strstr(str, "direction:") || !ft_strstr(str, "center:") || \
											!ft_strstr(str, "alpha:"))
			return ;
		objects[*n].type = 't';
		objects[*n].center = parse_vector(ft_strstr(str, "center:"));
        objects[*n].norm = parse_vector(ft_strstr(str, "direction:"));
		objects[*n].alpha = ft_atof(ft_strstr(str, "alpha:") + 6);
		objects[*n].color = parse_color(ft_strstr(str, "color:"));
		get_object_parameters(&(objects[*n]), str);
        ++(*n);
	}
}

void			parse_sources(t_cl_source *sources, char *str)
{
    int k = 0;

	while (ft_strstr(str, "light:"))
	{
		str = ft_strstr(str, "light:") + 1;
		if (!ft_strstr(str, "type:"))
			continue ;
		sources[k].type = parse_type(ft_strstr(str, "type:") \
												+ ft_strlen("type:"));
		if (ft_strstr(str, "position:"))
			sources[k].position = parse_vector(ft_strstr(str, "position:") \
												+ ft_strlen("position:"));
		if (ft_strstr(str, "direction:"))
			sources[k].position = parse_vector(ft_strstr(str, "direction:") \
												+ ft_strlen("direction:"));
		if (ft_strstr(str, "intensity:"))
			sources[k].intensity = ft_atof(ft_strstr(str, "intensity:") \
												+ ft_strlen("intensity:"));
        ++(k);
        if (k >= N_SRC)
            break ;
	}
}

void		parse_viewpoint(cl_float3 *vp, char *str)
{
	str = ft_strstr(str, "viewpoint:");
	if (str)
		*vp = parse_vector(str + ft_strlen("viewpoint:"));
	else
		*vp = return_zero_vector();
}

void		parse_camera_angles(t_matrix *rot, char *str)
{
    cl_float3   angles;

	str = ft_strstr(str, "camera:"); 
	if (str)
		angles = parse_vector(str + ft_strlen("camera:"));
	else
		angles = return_zero_vector();
	*rot = return_eig_rot_m(angles);
}

void        zero_objects_and_sources(t_cl_object *objects, t_cl_source *sources)
{
    int     i;

    i = -1;
    while (++i < N_OBJ)
        objects[i] = (const t_cl_object){0};
	i = -1;
	while (++i < N_SRC)
		sources[i] = (const t_cl_source){0};
}

void		ft_parse_scene(char *filename, t_scene *scene)
{
	int		fd;
	int		out;
	char	buffer[10000];
    int     n;

    n = 0;
	fd = open(filename, O_RDONLY);
	out = read(fd, buffer, 10000);
	buffer[out] = '\0';
    zero_objects_and_sources(scene->objects, scene->sources);
	parse_plane(scene->objects, buffer, &n);
	parse_sphere(scene->objects, buffer, &n);
	parse_cylinder(scene->objects, buffer, &n);
	parse_cone(scene->objects, buffer, &n);
	parse_sources(scene->sources, buffer);
	parse_viewpoint(&(scene->viewpoint), buffer);
	parse_camera_angles(&(scene->rot_matrix), buffer);
	close(fd);
}

