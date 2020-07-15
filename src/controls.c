/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 12:02:23 by fwisp             #+#    #+#             */
/*   Updated: 2020/07/15 20:02:50 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void    mouse_controls(t_sdl sdl, t_scene *scene, SDL_Event event)
{
    cl_float3		shift;
    cl_int4			*z;
    
    shift = (cl_float3){{0, 0, 1}};
	shift = ft_vrot(shift, scene->rot_matrix);
	if(event.wheel.y > 0)
	{
		scene->viewpoint.s[0] += shift.s[0];
		scene->viewpoint.s[1] += shift.s[1];
		scene->viewpoint.s[2] += shift.s[2];
	}
	else if(event.wheel.y < 0)
	{
		scene->viewpoint.s[0] -= shift.s[0];
		scene->viewpoint.s[1] -= shift.s[1];
		scene->viewpoint.s[2] -= shift.s[2];
	}
	z = ft_draw(sdl, *scene);
	// free(z);
}

static void    camera_movement(t_sdl sdl, t_scene *scene, SDL_Event event)
{
    cl_float3		shift;
    cl_int4			*z;

    shift = (cl_float3){{0, 0, 0}};
    if (event.key.keysym.sym == SDLK_d)
		shift = ft_vrot((cl_float3){{1, 0, 0}}, scene->rot_matrix);
	else if (event.key.keysym.sym == SDLK_a)
		shift = ft_vrot((cl_float3){{-1, 0, 0}}, scene->rot_matrix);
	else if (event.key.keysym.sym == SDLK_w)
		shift = ft_vrot((cl_float3){{0, 1, 0}}, scene->rot_matrix);
	else if (event.key.keysym.sym == SDLK_s)
		shift = ft_vrot((cl_float3){{0, -1, 0}}, scene->rot_matrix);
	scene->viewpoint.s[0] += shift.s[0];
	scene->viewpoint.s[1] += shift.s[1];
	scene->viewpoint.s[2] += shift.s[2];
	z = ft_draw(sdl, *scene);
	// free(z);
}

static void    camera_rotation(t_sdl sdl, t_scene *scene, SDL_Event event)
{
    cl_int4			*z;

	if (event.key.keysym.sym == SDLK_DOWN)
		scene->cam_angles.s[0] += 5;
	else if (event.key.keysym.sym == SDLK_UP)
		scene->cam_angles.s[0] -= 5;
	else if (event.key.keysym.sym == SDLK_RIGHT)
		scene->cam_angles.s[1] += 5;
	else if (event.key.keysym.sym == SDLK_LEFT)
		scene->cam_angles.s[1] -= 5;
	else if (event.key.keysym.sym == SDLK_0)
	{
		scene->viewpoint = scene->startviewpoint;
		scene->cam_angles.s[0] = 0;
		scene->cam_angles.s[1] = 0;
	}
	scene->rot_matrix = return_eig_rot_m(scene->cam_angles);
	z = ft_draw(sdl, *scene);
	// free(z);
}

static void    keyboard_effects(t_sdl sdl, t_scene *scene, const Uint8	*keystate)
{
    cl_int4			*z;
    
	if (keystate[SDL_SCANCODE_RETURN])
		SDL_SaveBMP(sdl.screen, "screenshot.bmp");
	if (keystate[SDL_SCANCODE_SPACE] && keystate[SDL_SCANCODE_O])
		scene->effect = scene->effect != 's' ? 's' : 0;
	if (keystate[SDL_SCANCODE_SPACE] && keystate[SDL_SCANCODE_G])
		scene->effect = scene->effect != 'g' ? 'g' : 0;
	if (keystate[SDL_SCANCODE_SPACE] && keystate[SDL_SCANCODE_P])
		scene->effect = scene->effect != 'p' ? 'p' : 0;
	if (keystate[SDL_SCANCODE_SPACE] && keystate[SDL_SCANCODE_I])
		scene->effect = scene->effect != 'i' ? 'i' : 0;
	if (keystate[SDL_SCANCODE_SPACE] && keystate[SDL_SCANCODE_L])
		scene->effect = scene->effect != 'l' ? 'l' : 0;
	else if (keystate[SDL_SCANCODE_SPACE] && keystate[SDL_SCANCODE_B] )
		scene->effect = scene->effect != 'b' ? 'b' : 0;
	else if (keystate[SDL_SCANCODE_SPACE] && keystate[SDL_SCANCODE_E] \
									 && keystate[SDL_SCANCODE_KP_PLUS])
		scene->effect_int += scene->effect_int < 10 ? 1 : 0;
	else if (keystate[SDL_SCANCODE_SPACE] && keystate[SDL_SCANCODE_E] \
									&& keystate[SDL_SCANCODE_KP_MINUS])
		scene->effect_int -= scene->effect_int > 1 ? 1 : 0;
    z = ft_draw(sdl, *scene);
	// free(z);
}

void		controls(t_sdl sdl, t_scene scene)
{
	SDL_Event		event;
	const Uint8			*keystate;

	keystate = SDL_GetKeyboardState(NULL);
	while (1)
	{
		if (SDL_PollEvent(&event))
		{		
			if (event.type == SDL_QUIT)
				break ;
			else if(event.type == SDL_MOUSEWHEEL)
				mouse_controls(sdl, &scene, event);
			else if (event.type == SDL_KEYDOWN)
			{
				camera_movement(sdl, &scene, event);
				camera_rotation(sdl, &scene, event);
				keyboard_effects(sdl, &scene, keystate);
				if (event.key.keysym.sym == SDLK_ESCAPE || \
						event.key.keysym.sym == SDLK_q)
					break ;
			}
		}
	}
}