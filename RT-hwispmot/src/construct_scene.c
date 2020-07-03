/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 06:23:40 by hwispmot          #+#    #+#             */
/*   Updated: 2020/01/29 22:02:48 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

// void	check_sources(t_list *sources)
// {
// 	t_list	*tmp_list;
// 	float	sum;

// 	sum = 0.;
// 	tmp_list = sources;
// 	while (tmp_list)
// 	{
// 		sum += ((t_source *)(tmp_list->content))->intensity;
// 		tmp_list = tmp_list->next;
// 	}
// 	tmp_list = sources;
// 	while (tmp_list)
// 	{
// 		(*((t_source *)(tmp_list->content))).intensity /= sum;
// 		tmp_list = tmp_list->next;
// 	}
// }

t_scene	construct_scene(char *fname)
{
	t_scene		scene;
	cl_float3	cam_ang;
	int			i;
	float		phi;
	int			color[3];
	// ft_parse_scene(fname, &scene);
	// check_sources(scene.sources);
	fname[0] = 1;
	
	scene.cl_lim.max = 1.0f;
	scene.cl_lim.min = 0.001f;
	scene.tr_lim.max = 400000.0f;
	scene.tr_lim.min = 0.001f;

	cam_ang.s[0] = 0;
	cam_ang.s[1] = 0;
	scene.rot_matrix = return_eig_rot_m(cam_ang);

	/*scene.startviewpoint = (cl_float3){{ 0., 0., 0.}};
	scene.viewpoint = scene.startviewpoint;

	color[0] = 100;
	color[1] = 0;
	color[2] = 0;
	scene.objects[0].center = (cl_float3){{ 0., 0., 10. }};
	scene.objects[0].radius = 3.f;
	scene.objects[0].color = (cl_int3){{color[0], color[1], color[2]}};
	scene.objects[0].specular = 0;
	scene.objects[0].reflective = 0.f;
	scene.objects[0].type = 's';
	scene.objects[0].texture = 0;
	scene.objects[0].textype = 'c';
	scene.objects[0].scale = (cl_float2){{ 1.0f, 1.0f}};
	scene.objects[0].shift = (cl_float2){{ 0.0f, 0.0f}};

	scene.sources[0].position = scene.viewpoint;
	scene.sources[0].intensity = 1.f;
	scene.sources[0].type = 'p';
	i = 0;
	phi = 0;*/
////---------------------------------------------------------Plates and spheres -------------------------------------------------------------------
	scene.startviewpoint = (cl_float3){{ 0., 0., -25.0}};
	scene.viewpoint = scene.startviewpoint;

	i = -1;
	phi = 0;
	while (++i < 8)
	{
		color[0] = (int)(255 * (cos(phi) + 1.) / 2);
		color[1] = (int)(255 * (sin(phi) + 1.) / 2);
		color[2] = (int)(255 * (cos(phi) * sin(phi) + 0.5)); 
		scene.objects[i].center = (cl_float3){{ 5. * cos(phi), 5. * sin(phi), 0. }};
		scene.objects[i].radius = 0.5f;
		scene.objects[i].color = (cl_int3){{color[0], color[1], color[2]}};
		scene.objects[i].specular = 0;
		scene.objects[i].reflective = 0.f;
		scene.objects[i].type = 's';
		scene.objects[i].texture = 0;
		scene.objects[i].textype = 'c';
		scene.objects[i].scale = (cl_float2){{ 1.0f, 1.0f}};
		scene.objects[i].shift = (cl_float2){{ 0.0f, 0.0f}};
		phi += M_PI/4;
	}

	i -= 1;
	phi = M_PI;
	while (++i < 12)
	{
		color[0] = 200;//(int)(255 * (cos(phi) + 1.) / 2);
		color[1] = 200;//(int)(255 * (sin(phi) + 1.) / 2);
		color[2] = 200;//(int)(255 * (cos(phi) * sin(phi) + 0.5)); 
		scene.objects[i].center = (cl_float3){{15. * cos(phi), 15. * sin(phi), 0.}};
		scene.objects[i].norm = (cl_float3){{cos(phi), sin(phi), 0.}};
		scene.objects[i].color = (cl_int3){{color[0], color[1], color[2]}};
		scene.objects[i].specular = 0;
		scene.objects[i].reflective = 0.f;
		scene.objects[i].type = 'p';
		scene.objects[i].texture = 0;
		scene.objects[i].textype = 'c';
		scene.objects[i].scale = (cl_float2){{ 1.0f, 1.0f}};
		scene.objects[i].shift = (cl_float2){{ 0.0f, 0.0f}};
		phi += M_PI/2;
	}

		color[0] = 100;//(int)(255 * (cos(phi) + 1.) / 2);
		color[1] = 0;//(int)(255 * (sin(phi) + 1.) / 2);
		color[2] = 0;//(int)(255 * (cos(phi) * sin(phi) + 0.5)); 
		scene.objects[i].center = (cl_float3){{0., 0., 5.}};
		scene.objects[i].norm = (cl_float3){{0, 0, 1.}};
		scene.objects[i].color = (cl_int3){{color[0], color[1], color[2]}};
		scene.objects[i].specular = 0;
		scene.objects[i].reflective = 0.f;
		scene.objects[i].type = 'p';
		scene.objects[i].texture = 0;
		scene.objects[i].textype = 'c';
		scene.objects[i].scale = (cl_float2){{ 1.0f, 1.0f}};
		scene.objects[i].shift = (cl_float2){{ 0.0f, 0.0f}};
		i++;
		color[0] = 0;//(int)(255 * (cos(phi) + 1.) / 2);
		color[1] = 100;//(int)(255 * (sin(phi) + 1.) / 2);
		color[2] = 100;//(int)(255 * (cos(phi) * sin(phi) + 0.5)); 
		scene.objects[i].center = (cl_float3){{0., 0., -50.}};
		scene.objects[i].norm = (cl_float3){{0, 0, -1.}};
		scene.objects[i].color = (cl_int3){{color[0], color[1], color[2]}};
		scene.objects[i].specular = 0;
		scene.objects[i].reflective = 0.f;
		scene.objects[i].type = 'p';
		scene.objects[i].texture = 0;
		scene.objects[i].textype = 'c';
		scene.objects[i].scale = (cl_float2){{ 1.0f, 1.0f}};
		scene.objects[i].shift = (cl_float2){{ 0.0f, 0.0f}};
		
	scene.sources[0].position = (cl_float3){{0., 0., 16.5}};//scene.viewpoint;//(cl_float3){{5 * cos(phi), 5 * sin(phi), -25.0f}};
	scene.sources[0].intensity = 1.f;
	scene.sources[0].type = 'p';
	
	scene.sources[1].position = (cl_float3){{0., 0., -16.5}};
	scene.sources[1].intensity = 1.f;
	scene.sources[1].type = 'p';
	
	//-------------------------------------------------inside sphere---------------------------------------------
	/*i = 0;
	phi = 0;
	scene.startviewpoint = (cl_float3){{ 0., 0., .0}};
	scene.viewpoint = scene.startviewpoint;
	color[0] = 200;//(int)(255 * (cos(phi) + 1.) / 2);
	color[1] = 200;//(int)(255 * (sin(phi) + 1.) / 2);
	color[2] = 200;//(int)(255 * (cos(phi) * sin(phi) + 0.5)); 
	scene.objects[0].center = (cl_float3){{ 0., 0., .0}};
	scene.objects[0].radius = 10;
	scene.objects[0].color = (cl_int3){{color[0], color[1], color[2]}};
	scene.objects[0].specular = 0;
	scene.objects[0].reflective = 0.f;
	scene.objects[0].type = 's';
	scene.objects[0].texture = 0;
	scene.objects[0].textype = 'c';
	scene.objects[0].scale = (cl_float2){{ 1.0f, 1.0f}};
	scene.objects[0].shift = (cl_float2){{ 0.0f, 0.0f}};
	scene.sources[0].position = scene.viewpoint;
	scene.sources[0].intensity = 1.f;
	scene.sources[0].type = 'p';
	scene.sources[1].position = (cl_float3){{ 0., 0., -15}};
	scene.sources[1].intensity = 1.f;
	scene.sources[1].type = 'p';*/
	return (scene);
}
