/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pic.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 01:38:58 by hwispmot          #+#    #+#             */
/*   Updated: 2020/07/18 14:47:54 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_put_pixel(SDL_Surface *surface, int x, int y, cl_int4 ccolor)
{
	int		bpp;
	Uint32	pixel;
	Uint8	*p;

	bpp = surface->format->BytesPerPixel;
	if (ccolor.s[0] > 255)
		ccolor.s[0] = 255;
	if (ccolor.s[1] > 255)
		ccolor.s[1] = 255;	
	if (ccolor.s[2] > 255)
		ccolor.s[2] = 255;
	pixel = (SDL_MapRGB(surface->format, ccolor.s[0], ccolor.s[1], ccolor.s[2]));
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	if (bpp == 4)
		*(Uint32 *)p = pixel;
}

void	ft_draw(t_sdl sdl, t_scene scene)
{
	int			x;
	int			y;
	cl_int4		ccolor;
	cl_int4		*z;
	int			i;
	int			j;

	z = rt_cl(&(sdl.cl_inst), scene);
	if (scene.effect == 'a' && scene.effect_int > 1)
	{
		x = 0;	
		while (x < C_W * scene.effect_int)
		{
			y = 0;
			while (y < C_H * scene.effect_int)
			{
				i = -1;
				z[x / scene.effect_int * C_H + y / scene.effect_int] = (cl_int4){{0, 0, 0, 0}};
				while (++i < scene.effect_int)
				{
					j = -1;
					while (++j < scene.effect_int)
					{
							z[x / scene.effect_int * C_H + y / scene.effect_int].s[0] += z[((x + i) * scene.effect_int) * C_H + y + j].s[0];
							z[x / scene.effect_int * C_H + y / scene.effect_int].s[1] += z[((x + i) * scene.effect_int) * C_H + y + j].s[1];
							z[x / scene.effect_int * C_H + y / scene.effect_int].s[2] += z[((x + i) * scene.effect_int) * C_H + y + j].s[2];
					}
				}
				z[x / scene.effect_int * C_H + y / scene.effect_int].s[0] /= pow(scene.effect_int, 2);
				z[x / scene.effect_int * C_H + y / scene.effect_int].s[1] /= pow(scene.effect_int, 2);
				z[x / scene.effect_int * C_H + y / scene.effect_int].s[2] /= pow(scene.effect_int, 2);
				y += scene.effect_int;
			}
			x += scene.effect_int;
		}
	}
	else if (scene.effect != 0)
		effect(z, scene);
	x =  - 1;	
	while (++x < C_W)
	{
		y = - 1;
		while (++y < C_H)
		{
			ccolor = z[x * C_H + y];
			if (scene.effect == 'a')
				ccolor = z[x * C_H + y];
			// ccolor.s[0] = 255;
			// ccolor.s[1] = 255;
			// ccolor.s[2] = 0;
			ft_put_pixel(sdl.screen, x , y, ccolor);
		}
	}
	SDL_UpdateTexture(sdl.texture, NULL, sdl.screen->pixels, sdl.screen->pitch);
	SDL_RenderClear(sdl.renderer);
	SDL_RenderCopy(sdl.renderer, sdl.texture, NULL, NULL);
	SDL_RenderPresent(sdl.renderer);
	free(z);
	printf("redrawn %c %d\n", scene.effect, scene.effect_int);
}
