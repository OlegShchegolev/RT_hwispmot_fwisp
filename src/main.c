/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 21:16:51 by fwisp             #+#    #+#             */
/*   Updated: 2020/07/15 15:08:44 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				manage_processes(t_sdl sdl, t_scene scene, int argc, char **argv)
{
	cl_int4			*z;
	int				i;
	
	//sdl.cl_inst = initcl();
	scene = construct_scene(argv[1]);
	z = ft_draw(sdl, scene);
	//  free(z);
	if (argc > 2)
	{
		i = 1;
		while (++i < argc)
		{
			sleep(1);
			scene = construct_scene(argv[i]);
			z = ft_draw(sdl, scene);
			// free(z);
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
