/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 21:16:51 by fwisp             #+#    #+#             */
/*   Updated: 2020/08/12 16:13:40 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	loading_message(t_sdl *sdl)
{
	sdl->screen = SDL_LoadBMP("loading.bmp");
	SDL_UpdateTexture(sdl->texture, NULL, sdl->screen->pixels, sdl->screen->pitch);
	SDL_RenderClear(sdl->renderer);
	SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
	SDL_RenderPresent(sdl->renderer);
}

void				run_gui(t_sdl *sdl)
{
	SDL_Event		event;
	
	SDL_CreateWindowAndRenderer(C_W, C_H, 0, &(sdl->window), &(sdl->renderer));
	sdl->screen = SDL_CreateRGBSurface(0, C_W, C_H, 32, 0x00FF0000,\
							0x0000FF00, 0x000000FF, 0xFF000000);
	sdl->texture = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_ARGB8888,\
								SDL_TEXTUREACCESS_STREAMING, C_W, C_H);
	loading_message(sdl);
	progress_bar(sdl, 0.1);
	while(SDL_PollEvent(&event))
	{
	}
	sdl->cl_inst = initcl(sdl);
}

void				quit_sdl(t_sdl *sdl)
{
	SDL_FreeSurface(sdl->screen);
	SDL_DestroyWindow(sdl->window);
	SDL_Quit();
}

int					main(int argc, char **argv)
{
	t_sdl		sdl;
	t_scene		scene;
	t_controls	ctrl;

	if (argc < 2)
		return (0);
	sdl.scenes = argv;
	sdl.scene_num = argc - 1;
	scene.current_scene = 1;
	run_gui(&sdl);
	if (!construct_scene(argv[1], &scene, &sdl))
		ft_draw(sdl, scene);
	ctrl.scene = scene;
	ctrl.sdl = sdl;
	controls(sdl, scene);
	releasecl(&(sdl.cl_inst));
	quit_sdl(&sdl);
	return (0);
}