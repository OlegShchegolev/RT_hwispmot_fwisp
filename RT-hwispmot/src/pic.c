/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pic.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwispmot <hwispmot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 01:38:58 by hwispmot          #+#    #+#             */
/*   Updated: 2019/11/20 22:55:16 by hwispmot         ###   ########.fr       */
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

cl_int4	*ft_draw(t_sdl sdl, t_scene scene)
{
	t_lim		lim;
	int			x;
	int			y;
	cl_int4		ccolor;
	cl_int4		*z;

	lim.min = 1;
	lim.max = DMAX;
	z = rt_cl(&(sdl.cl_inst), scene);
	
	x =  - 1;	
	while (++x < C_W)
	{
		y = - 1;
		while (++y < C_H)
		{
			ccolor = z[x * C_H + y];
			ft_put_pixel(sdl.screen, x , y, ccolor);
		}
	}
	SDL_UpdateTexture(sdl.texture, NULL, sdl.screen->pixels, sdl.screen->pitch);
	SDL_RenderClear(sdl.renderer);
	SDL_RenderCopy(sdl.renderer, sdl.texture, NULL, NULL);
	SDL_RenderPresent(sdl.renderer);
	return(z);
}