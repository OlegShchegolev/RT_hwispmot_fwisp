/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 21:16:51 by fwisp             #+#    #+#             */
/*   Updated: 2020/07/15 14:52:02 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				manage_processes(t_sdl sdl, t_scene scene, int argc, char **argv)
{
	cl_int4			*z;
	int				i;
	
	sdl.cl_inst = initcl();
	if (argc == 2)
	{
		scene = construct_scene(argv[1]);
		z = ft_draw(sdl, scene);
		
	}
	else
	{
		i = 0;
		while (++i < argc)
		{
			scene = construct_scene(argv[i]);
			z = ft_draw(sdl, scene);
			sleep(1);
		}
	}
	controls(sdl, scene);
	SDL_FreeSurface(sdl.screen);
	SDL_DestroyWindow(sdl.window);
}

int					main(int argc, char **argv)
{
	t_sdl			sdl;
	t_scene			scene;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(C_W, C_H, 0, &(sdl.window), &(sdl.renderer));
	sdl.screen = SDL_CreateRGBSurface(0, C_W, C_H, 32, 0x00FF0000, \
							0x0000FF00, 0x000000FF, 0xFF000000);
	sdl.texture = SDL_CreateTexture(sdl.renderer, SDL_PIXELFORMAT_ARGB8888, \
								SDL_TEXTUREACCESS_STREAMING, C_W, C_H);
	if (argc < 2)
		return ;
	manage_processes(sdl, scene, argc, argv);
	SDL_Quit();
	return (0);
}
