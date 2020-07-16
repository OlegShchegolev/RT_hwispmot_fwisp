/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 12:02:23 by fwisp             #+#    #+#             */
/*   Updated: 2020/07/17 01:40:25 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void    mouse_controls(t_sdl sdl, t_scene *scene, SDL_Event event)
{
    cl_float3		shift;
    
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
	ft_draw(sdl, *scene);
}

static void    camera_movement(t_sdl sdl, t_scene *scene, GdkEventKey *event)
{
    cl_float3		shift;
	int				sym;

    shift = (cl_float3){{0, 0, 0}};
	sym = event->keyval;
	if (sym == GDK_KEY_d || sym == GDK_KEY_a || sym == GDK_KEY_w || sym == GDK_KEY_s)
    {
		if (sym == GDK_KEY_d)
			shift = ft_vrot((cl_float3){{1, 0, 0}}, scene->rot_matrix);
		else if (sym == GDK_KEY_a)
			shift = ft_vrot((cl_float3){{-1, 0, 0}}, scene->rot_matrix);
		else if (sym == GDK_KEY_w)
			shift = ft_vrot((cl_float3){{0, 1, 0}}, scene->rot_matrix);
		else if (sym == GDK_KEY_s)
			shift = ft_vrot((cl_float3){{0, -1, 0}}, scene->rot_matrix);
		scene->viewpoint.s[0] += shift.s[0];
		scene->viewpoint.s[1] += shift.s[1];
		scene->viewpoint.s[2] += shift.s[2];
		ft_draw(sdl, *scene);
	}
}

static void    camera_rotation(t_sdl sdl, t_scene *scene, GdkEventKey *event)
{
	int	sym;

	sym = event->keyval;
	if (sym == GDK_KEY_Down || sym == GDK_KEY_Up || sym == GDK_KEY_Right || sym == GDK_KEY_Left)
	{
		if (sym == GDK_KEY_Down)
			scene->cam_angles.s[0] += 5;
		else if (sym == GDK_KEY_Up)
			scene->cam_angles.s[0] -= 5;
		else if (sym == GDK_KEY_Right)
			scene->cam_angles.s[1] += 5;
		else if (sym == GDK_KEY_Left)
			scene->cam_angles.s[1] -= 5;
		scene->rot_matrix = return_eig_rot_m(scene->cam_angles);
		ft_draw(sdl, *scene);
	}
}

static void    keyboard_effects(t_sdl sdl, t_scene *scene, const Uint8	*keystate)
{
	if (keystate[SDL_SCANCODE_RETURN])
		SDL_SaveBMP(sdl.screen, "screenshot.bmp");
	if (keystate[SDL_SCANCODE_SPACE])
	{
		if (keystate[SDL_SCANCODE_O])
			scene->effect = scene->effect != 's' ? 's' : 0;
		if (keystate[SDL_SCANCODE_G])
			scene->effect = scene->effect != 'g' ? 'g' : 0;
		if (keystate[SDL_SCANCODE_P])
			scene->effect = scene->effect != 'p' ? 'p' : 0;
		if (keystate[SDL_SCANCODE_I])
			scene->effect = scene->effect != 'i' ? 'i' : 0;
		if (keystate[SDL_SCANCODE_L])
			scene->effect = scene->effect != 'l' ? 'l' : 0;
		else if (keystate[SDL_SCANCODE_B])
			scene->effect = scene->effect != 'b' ? 'b' : 0;
		else if (keystate[SDL_SCANCODE_E] && keystate[SDL_SCANCODE_KP_PLUS])
			scene->effect_int += scene->effect_int < 10 ? 1 : 0;
		else if (keystate[SDL_SCANCODE_E] && keystate[SDL_SCANCODE_KP_MINUS])
			scene->effect_int -= scene->effect_int > 1 ? 1 : 0;
    	ft_draw(sdl, *scene);
	}
}

void		controls2(t_sdl sdl, t_scene *scene, GdkEventKey *event)
{
	// const Uint8			*keystate;
    if (event->keyval == GDK_KEY_Escape)
        gtk_main_quit();
    else
    {
        camera_rotation(sdl, scene, event);
		camera_movement(sdl, scene, event);
	}
	// keystate = SDL_GetKeyboardState(NULL);
	// while (1)
	// {
	// 	if (SDL_PollEvent(&event))
	// 	{		
	// 		if (event.type == SDL_QUIT)
	// 			break ;
	// 		else if(event.type == SDL_MOUSEWHEEL)
	// 			mouse_controls(sdl, &scene, event);
	// 		else if (event.type == SDL_KEYDOWN)
	// 		{
	// 			camera_movement(sdl, &scene, event);
	// 			camera_rotation(sdl, &scene, event);
	// 			keyboard_effects(sdl, &scene, keystate);
	// 			if (event.key.keysym.sym == SDLK_ESCAPE || \
	// 					event.key.keysym.sym == SDLK_q)
	// 				break ;
	// 		}
	// 	}
	// }
}