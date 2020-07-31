/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 21:16:51 by fwisp             #+#    #+#             */
/*   Updated: 2020/01/29 22:02:29 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_matrix	return_eig_rot_m(cl_float3 cam_ang)
{
	// int			i;
	// int			j;
	t_matrix	zero;

	// i = -1;
	// while (++i < 3)
	// {
	// 	j = -1;
	// 	while (++j < 3)
	// 		if (i != j)
	// 			zero.m[i][j] = 0;
	// 		else
	// 			zero.m[i][i] = 1;
	// }
	cam_ang.s[0] = cam_ang.s[0] * (3.14 / 180);
	cam_ang.s[1] = cam_ang.s[1] * (3.14 / 180);
	cam_ang.s[2] = cam_ang.s[2] * (3.14 / 180);
	
	zero.m[0][0] = cos(cam_ang.s[1]);
	zero.m[0][1] = 0;
	zero.m[0][2] = sin(cam_ang.s[1]);
	

	zero.m[1][0] = sin(cam_ang.s[1]) * sin(cam_ang.s[0]);
	zero.m[1][1] = cos(cam_ang.s[0]);
	zero.m[1][2] = - sin(cam_ang.s[0]) * cos(cam_ang.s[1]);
	

	zero.m[2][0] = - sin(cam_ang.s[1]) * cos(cam_ang.s[0]);
	zero.m[2][1] = sin(cam_ang.s[0]);
	zero.m[2][2] = cos(cam_ang.s[0]) * cos(cam_ang.s[1]);
	

	// zero.m[0][0] = cos(cam_ang.s[0]) * cos(cam_ang.s[2]) - cos(cam_ang.s[1]) * sin(cam_ang.s[0]) * sin(cam_ang.s[2]);
	// zero.m[0][1] = -cos(cam_ang.s[2]) * sin(cam_ang.s[0]) - cos(cam_ang.s[0]) * cos(cam_ang.s[1]) * sin(cam_ang.s[2]);
	// zero.m[0][2] = sin(cam_ang.s[1]) * sin(cam_ang.s[2]);


	// zero.m[1][0] = cos(cam_ang.s[1]) * cos(cam_ang.s[2]) * sin(cam_ang.s[0]) + cos(cam_ang.s[0]) * sin(cam_ang.s[2]);
	// zero.m[1][1] = cos(cam_ang.s[0]) * cos(cam_ang.s[1]) * cos(cam_ang.s[2]) - sin(cam_ang.s[0]) * sin(cam_ang.s[2]);
	// zero.m[1][2] = -cos(cam_ang.s[2]) * sin(cam_ang.s[1]);


	// zero.m[2][0] = sin(cam_ang.s[0]) * sin(cam_ang.s[1]);
	// zero.m[2][1] = cos(cam_ang.s[0]) * sin(cam_ang.s[1]);
	// zero.m[2][2] = cos(cam_ang.s[1]);
	return (zero);
}



cl_float3 make_degr_radians(cl_float3 cam_ang)
{
	cl_float3 cam_rad;

	cam_rad.x = cam_ang.x * (M_PI / 180);
	cam_rad.y = cam_ang.y * (M_PI / 180);
	cam_rad.z = cam_ang.z * (M_PI / 180);

	// cam_rad.x = cam_ang.s[0] * (M_PI / 180);
	// cam_rad.y = cam_ang.s[1] * (M_PI / 180);
	// cam_rad.z = cam_ang.s[2] * (M_PI / 180);
	return (cam_rad);
}

cl_float3	ft_vrot(cl_float3 a, t_matrix rot)
{
	cl_float3	res;

	res.s[0] = rot.m[0][0] * a.s[0] + rot.m[0][1] * a.s[1] + rot.m[0][2] * a.s[2];
	res.s[1] = rot.m[1][0] * a.s[0] + rot.m[1][1] * a.s[1] + rot.m[1][2] * a.s[2];
	res.s[2] = rot.m[2][0] * a.s[0] + rot.m[2][1] * a.s[1] + rot.m[2][2] * a.s[2];


	// res.s[0] = rot.m[0][0] * a.s[0] + rot.m[1][0] * a.s[1] + rot.m[2][0] * a.s[2];
	// res.s[1] = rot.m[0][1] * a.s[0] + rot.m[1][1] * a.s[1] + rot.m[2][1] * a.s[2];
	// res.s[2] = rot.m[0][2] * a.s[0] + rot.m[1][2] * a.s[1] + rot.m[2][2] * a.s[2];

	return (res);
}








cl_float3	rotate_vector(cl_float3 vec, cl_float3 rotate, int s)
{
	cl_float3 vec_res;

	vec_res = vec;
	if (rotate.s[0] != 0)
	{
		vec.s[1] = vec_res.s[1] * cos(s * rotate.s[0]) + vec_res.s[2] * sin(s * rotate.s[0]);
		vec.s[2] = -vec_res.s[1] * sin(s * rotate.s[0]) + vec_res.s[2] * cos(s * rotate.s[0]);
	}
	vec_res = vec;
	if (rotate.s[1] != 0)
	{
		vec.s[0] = vec_res.s[0] * cos(s * rotate.s[1]) + vec_res.s[2] * sin(s * rotate.s[1]);
		vec.s[2] = -vec_res.s[0] * sin(s * rotate.s[1]) + vec_res.s[2] * cos(s * rotate.s[1]);
	}
	vec_res = vec;
	if (rotate.s[2] != 0)
	{
		vec.s[0] = vec_res.s[0] * cos(s * rotate.s[2]) - vec_res.s[1] * sin(s * rotate.s[2]);
		vec.s[1] = vec_res.s[0] * sin(s * rotate.s[2]) + vec_res.s[1] * cos(s * rotate.s[2]);
	}


	// rotate = make_degr_radians(vec);
	// vec_res = vec;
	// if (rotate.x != 0)
	// {
	// 	vec.y = vec_res.y * cos(s * rotate.x) + vec_res.z * sin(s * rotate.x);
	// 	vec.z = -vec_res.y * sin(s * rotate.x) + vec_res.z * cos(s * rotate.x);
	// }
	// vec_res = vec;
	// if (rotate.y != 0)
	// {
	// 	vec.x = vec_res.x * cos(s * rotate.y) + vec_res.z * sin(s * rotate.y);
	// 	vec.z = -vec_res.x * sin(s * rotate.y) + vec_res.z * cos(s * rotate.y);
	// }
	// vec_res = vec;
	// if (rotate.z != 0)
	// {
	// 	vec.x = vec_res.x * cos(s * rotate.z) - vec_res.y * sin(s * rotate.z);
	// 	vec.y = vec_res.x * sin(s * rotate.z) + vec_res.y * cos(s * rotate.z);
	// }
	// return (vec);


	return (vec);
}


// cl_float3 make_degr_radians(cl_float3 cam_ang)
// {
// 	cl_float3 cam_rad;

// 	cam_rad.s[0] = cam_ang.s[0] * (M_PI_F / 180);
// 	cam_rad.s[1] = cam_ang.s[1] * (M_PI_F / 180);
// 	cam_rad.s[2] = cam_ang.s[2] * (M_PI_F / 180);
// 	return (cam_rad);
// }


// cl_float3	rotate_vector(cl_float3 vec, cl_float3 rotate, int s)
// {
// 	cl_float3 vec_res;

// 	rotate = make_degr_radians(vec);
// 	vec_res = vec;
// 	if (rotate.s[0] != 0)
// 	{
// 		vec.s[1] = vec_res.s[1] * cos(s * rotate.s[0]) + vec_res.s[2] * sin(s * rotate.s[0]);
// 		vec.s[2] = -vec_res.s[1] * sin(s * rotate.s[0]) + vec_res.s[2] * cos(s * rotate.s[0]);
// 	}
// 	vec_res = vec;
// 	if (rotate.s[1] != 0)
// 	{
// 		vec.s[0] = vec_res.s[0] * cos(s * rotate.s[1]) + vec_res.s[2] * sin(s * rotate.s[1]);
// 		vec.s[2] = -vec_res.s[0] * sin(s * rotate.s[1]) + vec_res.s[2] * cos(s * rotate.s[1]);
// 	}
// 	vec_res = vec;
// 	if (rotate.s[2] != 0)
// 	{
// 		vec.s[0] = vec_res.s[0] * cos(s * rotate.s[2]) - vec_res.s[1] * sin(s * rotate.s[2]);
// 		vec.s[1] = vec_res.s[0] * sin(s * rotate.s[2]) + vec_res.s[1] * cos(s * rotate.s[2]);
// 	}
// 	return (vec);
// }






void				wait_quit(t_sdl sdl, t_scene scene)
{
	SDL_Event		event;
	cl_float3		cam_ang;
	cl_float3		shift;
	cl_int4			*z;

	cam_ang.s[0] = 0;
	cam_ang.s[1] = 0;
	cam_ang.s[2] = 0;


	// cam_ang.x = 0;
	// cam_ang.y = 0;
	// cam_ang.z = 0;
	// cam_ang = make_degr_radians(cam_ang);

	scene.cam_ang = cam_ang;



	z = ft_draw(sdl, scene);
	
	while (1)
	{

		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				break ;
			else if (event.type == SDL_MOUSEMOTION)
			{
				printf("Object id (%d), type (%c)\n",
                z[event.motion.x * C_H + event.motion.y].s[3], 
				scene.objects[z[event.motion.x * C_H + event.motion.y].s[3]].type);
			}
			else if(event.type == SDL_MOUSEWHEEL)
			{
				shift = (cl_float3){{0, 0, 1}};
				shift = ft_vrot(shift, scene.rot_matrix);
				shift = rotate_vector(shift, scene.cam_ang, 1);
				if(event.wheel.y > 0)
				{
					scene.viewpoint.s[0] += shift.s[0];
					scene.viewpoint.s[1] += shift.s[1];
					scene.viewpoint.s[2] += shift.s[2];
				}
				else if(event.wheel.y < 0)
				{
					scene.viewpoint.s[0] -= shift.s[0];
					scene.viewpoint.s[1] -= shift.s[1];
					scene.viewpoint.s[2] -= shift.s[2];
				}
				z = ft_draw(sdl, scene);
			}
			else if (event.type == SDL_KEYDOWN)
			{
				shift = (cl_float3){{0, 0, 0}};
				if (event.key.keysym.sym == SDLK_d)
					shift = ft_vrot((cl_float3){{1, 0, 0}}, scene.rot_matrix);
				if (event.key.keysym.sym == SDLK_a)
					shift = ft_vrot((cl_float3){{-1, 0, 0}}, scene.rot_matrix);
				if (event.key.keysym.sym == SDLK_w)
					shift = ft_vrot((cl_float3){{0, 1, 0}}, scene.rot_matrix);
				if (event.key.keysym.sym == SDLK_s)
					shift = ft_vrot((cl_float3){{0, -1, 0}}, scene.rot_matrix);



				scene.viewpoint.s[0] += shift.s[0];
				scene.viewpoint.s[1] += shift.s[1];
				scene.viewpoint.s[2] += shift.s[2];




				if (event.key.keysym.sym == SDLK_DOWN)
					// cam_ang.s[0] += 5;
					cam_ang.x += 5;
				if (event.key.keysym.sym == SDLK_UP)
					// cam_ang.s[0] -= 5;
					cam_ang.x -= 5;
				if (event.key.keysym.sym == SDLK_RIGHT)
					// cam_ang.s[1] += 5;
					cam_ang.y += 5;
				if (event.key.keysym.sym == SDLK_LEFT)
					// cam_ang.s[1] -= 5;
					cam_ang.y -= 5;
				if (event.key.keysym.sym == SDLK_q)
					// cam_ang.s[2] += 5;
					cam_ang.z += 5;
				if (event.key.keysym.sym == SDLK_e)
					// cam_ang.s[2] -= 5;
					cam_ang.z += 5;



				if (event.key.keysym.sym == SDLK_0)
				{
					scene.viewpoint = scene.startviewpoint;
					cam_ang.s[0] = 0;
					cam_ang.s[1] = 0;
					cam_ang.s[2] = 0;

					// cam_ang.x = 0;
					// cam_ang.y = 0;
					// cam_ang.z = 0;
				}
				scene.rot_matrix = return_eig_rot_m(cam_ang);



				scene.cam_ang = cam_ang;
				// cam_ang = make_degr_radians(cam_ang);
				
				z = ft_draw(sdl, scene);
				if (event.key.keysym.sym == SDLK_ESCAPE)
					break ;
			}
				
		}
	}
	SDL_FreeSurface(sdl.screen);
	SDL_DestroyWindow(sdl.window);
}

int					main(int argc, char **argv)
{
	t_sdl			sdl;
	t_scene			scene;

	char olo = argv[0][0];
	olo= 'b';
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(C_W, C_H, 0, &(sdl.window), &(sdl.renderer));
	sdl.screen = SDL_CreateRGBSurface(0, C_W, C_H, 32, 0x00FF0000, \
							0x0000FF00, 0x000000FF, 0xFF000000);
	sdl.texture = SDL_CreateTexture(sdl.renderer, SDL_PIXELFORMAT_ARGB8888, \
								SDL_TEXTUREACCESS_STREAMING, C_W, C_H);

	if (argc == 2)
	{
		sdl.cl_inst = initcl();
		scene = construct_scene(argv[1]);
		wait_quit(sdl, scene);
	}
	
	SDL_Quit();
	return (0);
}
