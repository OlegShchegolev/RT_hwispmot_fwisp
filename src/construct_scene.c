/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 06:23:40 by hwispmot          #+#    #+#             */
/*   Updated: 2020/07/15 03:12:11 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_scene	construct_scene(char *fname)
{
	t_scene		scene;
	cl_float3	cam_ang;
	ft_parse_scene(fname, &scene);
	check_sources(scene.sources);
	
	scene.startviewpoint = scene.viewpoint;
	scene.cl_lim.max = 1.0f;
	scene.cl_lim.min = 0.001f;
	scene.tr_lim.max = 400000.0f;
	scene.tr_lim.min = 0.000000000001f;
	scene.effect = 0;
	scene.effect_int = 3;

	cam_ang.s[0] = 0;
	cam_ang.s[1] = 0;
	scene.rot_matrix = return_eig_rot_m(cam_ang);

	return (scene);
}
