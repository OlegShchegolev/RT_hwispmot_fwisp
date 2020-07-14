/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shchegolev <shchegolev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 21:16:51 by fwisp             #+#    #+#             */
/*   Updated: 2020/07/14 23:15:48 by shchegolev       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_matrix	return_eig_rot_m(cl_float3 cam_ang)
{
	int			i;
	int			j;
	t_matrix	zero;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			if (i != j)
				zero.m[i][j] = 0;
			else
				zero.m[i][i] = 1;
	}
	cam_ang.s[0] = cam_ang.s[0] * (3.14 / 180);
	cam_ang.s[1] = cam_ang.s[1] * (3.14 / 180);
	
	zero.m[0][0] = cos(cam_ang.s[1]);
	zero.m[0][1] = 0;
	zero.m[0][2] = sin(cam_ang.s[1]);

	zero.m[1][0] = sin(cam_ang.s[1]) * sin(cam_ang.s[0]);
	zero.m[1][1] = cos(cam_ang.s[0]);
	zero.m[1][2] = - sin(cam_ang.s[0]) * cos(cam_ang.s[1]);

	zero.m[2][0] = - sin(cam_ang.s[1]) * cos(cam_ang.s[0]);
	zero.m[2][1] = sin(cam_ang.s[0]);
	zero.m[2][2] = cos(cam_ang.s[0]) * cos(cam_ang.s[1]);

	return (zero);
}

cl_float3	ft_vrot(cl_float3 a, t_matrix rot)
{
	cl_float3	res;

	res.s[0] = rot.m[0][0] * a.s[0] + rot.m[0][1] * a.s[1] + rot.m[0][2] * a.s[2];
	res.s[1] = rot.m[1][0] * a.s[0] + rot.m[1][1] * a.s[1] + rot.m[1][2] * a.s[2];
	res.s[2] = rot.m[2][0] * a.s[0] + rot.m[2][1] * a.s[1] + rot.m[2][2] * a.s[2];
	return (res);
}

void				wait_quit(t_sdl sdl, t_scene scene)
{
	SDL_Event		event;
	cl_float3		cam_ang;
	cl_float3		shift;
	cl_int4			*z;
	const Uint8			*keystate;

	cam_ang.s[0] = 0;
	cam_ang.s[1] = 0;
	z = ft_draw(sdl, scene);
	keystate = SDL_GetKeyboardState(NULL);
	while (1)
	{
		
		
		if (SDL_PollEvent(&event))
		{
			
			
			if (event.type == SDL_QUIT)
				break ;
			// else if (event.type == SDL_MOUSEMOTION)
			// {
			// 	printf("Object id (%d), type (%c)\n",
            //     z[event.motion.x * C_H + event.motion.y].s[3], 
			// 	scene.objects[z[event.motion.x * C_H + event.motion.y].s[3]].type);
			// }
			else if(event.type == SDL_MOUSEWHEEL)
			{
				shift = (cl_float3){{0, 0, 1}};
				shift = ft_vrot(shift, scene.rot_matrix);
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
				if ( keystate[SDL_SCANCODE_SPACE] && keystate[SDL_SCANCODE_O] )
				{
					if (scene.effect != 's')
						scene.effect = 's';
					else
						scene.effect = 0;
				}
				if ( keystate[SDL_SCANCODE_SPACE] && keystate[SDL_SCANCODE_G] )
				{
					if (scene.effect != 'g')
						scene.effect = 'g';
					else
						scene.effect = 0;
				}
				if ( keystate[SDL_SCANCODE_SPACE] && keystate[SDL_SCANCODE_P] )
				{
					if (scene.effect != 'p')
						scene.effect = 'p';
					else
						scene.effect = 0;
				}
				if ( keystate[SDL_SCANCODE_SPACE] && keystate[SDL_SCANCODE_I] )
				{
					if (scene.effect != 'i')
						scene.effect = 'i';
					else
						scene.effect = 0;
				}
				if ( keystate[SDL_SCANCODE_SPACE] && keystate[SDL_SCANCODE_L] )
				{
					if (scene.effect != 'l')
						scene.effect = 'l';
					else
						scene.effect = 0;
				}
				else if ( keystate[SDL_SCANCODE_SPACE] && keystate[SDL_SCANCODE_E] && keystate[SDL_SCANCODE_KP_PLUS])
				{
					if (scene.effect_int < 10)
						scene.effect_int++;
				}
				else if ( keystate[SDL_SCANCODE_SPACE] && keystate[SDL_SCANCODE_E] && keystate[SDL_SCANCODE_KP_MINUS])
				{
					if (scene.effect_int > 1)
						scene.effect_int--;
				}
				else if ( keystate[SDL_SCANCODE_SPACE] && keystate[SDL_SCANCODE_B] )
				{
					if (scene.effect != 'b')
						scene.effect = 'b';
					else
						scene.effect = 0;
				}
				else if (event.key.keysym.sym == SDLK_d)
					shift = ft_vrot((cl_float3){{1, 0, 0}}, scene.rot_matrix);
				else if (event.key.keysym.sym == SDLK_a)
					shift = ft_vrot((cl_float3){{-1, 0, 0}}, scene.rot_matrix);
				else if (event.key.keysym.sym == SDLK_w)
					shift = ft_vrot((cl_float3){{0, 1, 0}}, scene.rot_matrix);
				else if (event.key.keysym.sym == SDLK_s)
					shift = ft_vrot((cl_float3){{0, -1, 0}}, scene.rot_matrix);
				scene.viewpoint.s[0] += shift.s[0];
				scene.viewpoint.s[1] += shift.s[1];
				scene.viewpoint.s[2] += shift.s[2];
				if (event.key.keysym.sym == SDLK_DOWN)
					cam_ang.s[0] += 5;
				else if (event.key.keysym.sym == SDLK_UP)
					cam_ang.s[0] -= 5;
				else if (event.key.keysym.sym == SDLK_RIGHT)
					cam_ang.s[1] += 5;
				else if (event.key.keysym.sym == SDLK_LEFT)
					cam_ang.s[1] -= 5;
				else if (event.key.keysym.sym == SDLK_0)
				{
					scene.viewpoint = scene.startviewpoint;
					cam_ang.s[0] = 0;
					cam_ang.s[1] = 0;
				}
				scene.rot_matrix = return_eig_rot_m(cam_ang);
				z = ft_draw(sdl, scene);
				free(z);
				if (event.key.keysym.sym == SDLK_ESCAPE || \
						event.key.keysym.sym == SDLK_q)
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
		// sdl.cl_inst = initcl();
		scene = construct_scene(argv[1]);
		wait_quit(sdl, scene);
	}
	SDL_Quit();
	return (0);
}
