/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shchegolev <shchegolev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 06:23:40 by hwispmot          #+#    #+#             */
/*   Updated: 2020/07/14 23:27:04 by shchegolev       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

// void	check_sources(t_list *sources)
// {
// 	t_list	*tmp_list;
// 	float	sum;

// 	sum = 0.;
// 	tmp_list = sources;
// 	while (tmp_list)]
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

void	print_object(t_cl_object object)
{
	printf("%c %f\n", (char)object.type, (float)object.radius);
}

t_scene	construct_scene(char *fname)
{
	t_scene		scene;
	cl_float3	cam_ang;
	// ft_parse_scene(fname, &scene);
	// check_sources(scene.sources);
	
	scene.cl_lim.max = 1.0f;
	scene.cl_lim.min = 0.001f;
	scene.tr_lim.max = 400000.0f;
	scene.tr_lim.min = 0.000000000001f;
	scene.effect = 0;
	scene.effect_int = 3;

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

	// scene.objects[0].center = (cl_float3){{ -5.0, 4.0, -15.0 }};
	// scene.objects[0].radius = 2.0f;
	// scene.objects[0].color = (cl_int3){{10, 110, 120}};
	// scene.objects[0].specular = 1;
	// scene.objects[0].reflective = 0.0f;
	// scene.objects[0].type = 's';
	// scene.objects[0].texture = 2;
	// scene.objects[0].textype = 'c';
	// scene.objects[0].scale = (cl_float2){{ 1.0f, 1.0f}};
	// scene.objects[0].shift = (cl_float2){{ 0.0f, 0.0f}};

	scene.objects[1].center = (cl_float3){{-8.0f, 2.0f, -5.0f}};
	scene.objects[1].radius = 2.7f;
	scene.objects[1].color = (cl_int3){{255, 2, 120}};
	scene.objects[1].specular = 1;
	scene.objects[1].reflective = 0.0f;
	scene.objects[1].type = 's';
	scene.objects[1].texture = 1;
	scene.objects[1].textype = 'c';
	scene.objects[1].scale = (cl_float2){{ 1.0f, 1.0f}};
	scene.objects[1].shift = (cl_float2){{ 0.0f, 0.0f}};
	// scene.objects[1].slice[0] = (cl_float4){{ 0.50f, 0.50f, 0.0f, 0.3f}};
	// scene.objects[1].slice_side[0] = 2;
	scene.objects[1].negative = 1;

	scene.objects[2].center = (cl_float3){{0.0f, 0.0f, 0.0f}};
	scene.objects[2].norm = (cl_float3){{0.0f, 0.0f, 1.0f}};
	scene.objects[2].color = (cl_int3){{2, 2, 120}};
	scene.objects[2].specular = 1;
	scene.objects[2].reflective = 0.0f;
	scene.objects[2].type = 'p';
	scene.objects[2].texture = 2;
	scene.objects[2].textype = 'c';
	scene.objects[2].scale = (cl_float2){{ 3.0f, 5.0f}};
	scene.objects[2].shift = (cl_float2){{ 0.0f, 0.0f}};
	// scene.objects[2].slice[0] = (cl_float4){{ 0.50f, -0.50f, 0.50f, 5.0f}};
	// scene.objects[2].slice_side[0] = 2;
	// scene.objects[2].slice[1] = (cl_float4){{ 0.50f, -0.50f, 0.50f, 0.0f}};
	// scene.objects[2].slice_side[1] = 1;
	// scene.objects[2].slice[2] = (cl_float4){{ 0.50f, 0.20f, 0.0f, 0.0f}};
	// scene.objects[2].slice_side[2] = 2;
	// scene.objects[2].slice[3] = (cl_float4){{ 0.50f, 0.20f, 0.0f, -5.0f}};
	// scene.objects[2].slice_side[3] = 1;
	scene.objects[2].negative = 0;
	// scene.objects[3].center = (cl_float3){{0.0f, 0.0f, 0.0f}};
	// scene.objects[3].norm = (cl_float3){{0.0f, 1.0f, 0.0f}};
	// scene.objects[3].color = (cl_int3){{120, 120, 120}};
	// scene.objects[3].specular = 1;
	// scene.objects[3].reflective = 0.2f;
	// scene.objects[3].type = 'p';
	// scene.objects[3].texture = 2;
	// scene.objects[3].textype = 'c';
	// scene.objects[3].scale = (cl_float2){{ 3.0f, 5.0f}};
	// scene.objects[3].shift = (cl_float2){{ 0.0f, 0.0f}};
	// scene.objects[3].slice = (cl_float4){{ 0.50f, 0.50f, 0.0f, 0.0f}};
	// scene.objects[3].slice_side = 0;

	scene.objects[4].center = (cl_float3){{5.0f, 2.0f, -5.0f}};
	scene.objects[4].norm = (cl_float3){{1.0f, 0.0f, 0.0f}};
	scene.objects[4].radius = 2.0f;
	scene.objects[4].color = (cl_int3){{2, 100, 20}};
	scene.objects[4].specular = 1;
	scene.objects[4].reflective = 0.0f;
	scene.objects[4].type = 'c';
	scene.objects[4].texture = 2;
	scene.objects[4].textype = 'c';
	scene.objects[4].scale = (cl_float2){{ 3.0f, 5.0f}};
	scene.objects[4].shift = (cl_float2){{ 0.0f, 0.0f}};

	scene.objects[4].slice[0] = (cl_float4){{ 0.50f, 0.50f, 0.0f, 0.0f}};
	scene.objects[4].slice_side[0] = 1;
	scene.objects[4].negative = 0;
	// scene.objects[5].center = (cl_float3){{-1.0f, 7.0f, -5.0f}};
	// scene.objects[5].norm = (cl_float3){{0.4f, 0.916f, 0.0f}};
	// scene.objects[5].alpha = 0.4f;
	// scene.objects[5].color = (cl_int3){{2, 100, 20}};
	// scene.objects[5].specular = 1;
	// scene.objects[5].reflective = 0.2f;
	// scene.objects[5].type = 't';
	// scene.objects[5].texture = 2;
	// scene.objects[5].textype = 'c';
	// scene.objects[5].scale = (cl_float2){{ 3.0f, 5.0f}};
	// scene.objects[5].shift = (cl_float2){{ 0.0f, 0.0f}};

	// scene.objects[6].center = (cl_float3){{ 1.0, 4.0, -15.0 }};
	// scene.objects[6].radius = 2.0f;
	// scene.objects[6].color = (cl_int3){{251, 250, 237}};
	// scene.objects[6].specular = 1;
	// scene.objects[6].reflective = 0.0f;
	// scene.objects[6].type = 's';
	// scene.objects[6].texture = 6;
	// scene.objects[6].textype = 'b';
	// scene.objects[6].scale = (cl_float2){{ 1.0f, 1.0f}};
	// scene.objects[6].shift = (cl_float2){{ 0.0f, 0.0f}};

	// scene.objects[7].center = (cl_float3){{ 6.0, 4.0, -15.0 }};
	// scene.objects[7].radius = 2.0f;
	// scene.objects[7].color = (cl_int3){{200, 200, 200}};
	// scene.objects[7].specular = 1;
	// scene.objects[7].reflective = 0.0f;
	// scene.objects[7].type = 's';
	// scene.objects[7].texture = 7;
	// scene.objects[7].textype = 'd';
	// scene.objects[7].scale = (cl_float2){{ 1.0f, 1.0f}};
	// scene.objects[7].shift = (cl_float2){{ 0.0f, 0.0f}};
	

	// scene.objects[8].center = (cl_float3){{-5.0f, 5.0f, -10.0f}};
	// scene.objects[8].norm = (cl_float3){{0.0f, 1.0f,  0.0f}};
	// scene.objects[8].radius = 2.0f;
	// scene.objects[8].color = (cl_int3){{2, 100, 20}};
	// scene.objects[8].specular = 1;
	// scene.objects[8].reflective = 0.1f;
	// scene.objects[8].type = 'c';
	// scene.objects[8].texture = 1;
	// scene.objects[8].textype = 'o';
	// scene.objects[8].scale = (cl_float2){{ 2.0f, 2.0f}};
	// scene.objects[8].shift = (cl_float2){{ 0.0f, 0.0f}};

	// scene.objects[9].center = (cl_float3){{ 6.0f, 9.0f, -15.0f }};
	// scene.objects[9].radius = 2.0f;
	// scene.objects[9].color = (cl_int3){{50, 50, 180}};
	// scene.objects[9].specular = 1;
	// scene.objects[9].reflective = 0.0f;
	// scene.objects[9].type = 's';
	// scene.objects[9].texture = 1;
	// scene.objects[9].textype = 'o';
	// scene.objects[9].scale = (cl_float2){{ 1.0f, 1.0f}};
	// scene.objects[9].shift = (cl_float2){{ 0.0f, 0.0f}};

	// scene.objects[10].center = (cl_float3){{ 1.0f, 9.0f, -15.0f }};
	// scene.objects[10].radius = 2.0f;
	// scene.objects[10].color = (cl_int3){{50, 180, 180}};
	// scene.objects[10].specular = 1;
	// scene.objects[10].reflective = 0.0f;
	// scene.objects[10].type = 's';
	// scene.objects[10].texture = 8;
	// scene.objects[10].textype = 'o';
	// scene.objects[10].scale = (cl_float2){{ 1.0f, 1.0f}};
	// scene.objects[10].shift = (cl_float2){{ 0.0f, 0.0f}};
		
	// scene.sources[0].position = (cl_float3){{0.0f, 3.0f, -20.0f}};//scene.viewpoint;//(cl_float3){{5 * cos(phi), 5 * sin(phi), -25.0f}};
	// scene.sources[0].intensity = 0.2f;
	// scene.sources[0].type = 'p';
	
	// scene.sources[1].position = (cl_float3){{-20.0f, 10.0f, -50.0f}};
	// scene.sources[1].intensity = 0.4f;
	// scene.sources[1].type = 'p';
	ft_parse_scene(fname, &scene);
	printf("here %s\n", fname);
	for (int i = 0; i < 20; i++)
	{
		printf("%d ", i);
		print_object(scene.objects[i]);	
	}


	return (scene);
}
