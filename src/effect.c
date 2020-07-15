#include "rtv1.h"

void box_blur(cl_int4 *z, int r)
{
    cl_int4		sum;
	int			x;
	int			y;
	int			i;
	int			j;
	cl_int4		*tmp;

	tmp = (cl_int4 *)malloc(sizeof(cl_int4) * C_H * C_W);
	tmp = ft_memcpy(tmp, z, sizeof(cl_int4) * C_H * C_W);
	x =  - 1;	
	while (++x < C_W)
	{
		y = - 1;
		while (++y < C_H)
		{
			sum = (cl_int4){{0, 0, 0, 1}};
			i = -r - 1;
			while (++i < r+1)
			{
				j = -r - 1;
				while (++j < r+1)
				{
					if (x + i >= C_W || y + j >= C_H || x + i <= 0 || y + j <= 0)
						continue;
					sum.s[0] += tmp[(x + i) * C_H + (y+j)].s[0];
					sum.s[1] += tmp[(x + i) * C_H + (y+j)].s[1];
					sum.s[2] += tmp[(x + i) * C_H + (y+j)].s[2];
					sum.s[3]++;
				}
			}
			z[x * C_H + y].s[0] = sum.s[0] / sum.s[3];
			z[x * C_H + y].s[1] = sum.s[1] / sum.s[3];
			z[x * C_H + y].s[2] = sum.s[2] / sum.s[3];
		}
	}
	free(tmp);
}

void pixelize(cl_int4 *z, int r) {
    cl_int4		sum;
	int			x;
	int			y;
	int			i;
	int			j;
	cl_int4*	tmp;

	tmp = (cl_int4*)malloc(sizeof(cl_int4) * C_H * C_W);
	tmp = ft_memcpy(tmp, z, sizeof(cl_int4) * C_H * C_W);
	x =  - 1;	
	while (++x * r < C_W)
	{
		y = - 1;
		while (++y * r < C_H)
		{
			sum.s[0] = 0;
			sum.s[1] = 0;
			sum.s[2] = 0;
			sum.s[3] = 1;
			i = - 1;
			while (++i < r + 1)
			{
				j = - 1;
				while (++j < r + 1)
				{
					if (x * r + i >= C_W || y * r + j >= C_H || x * r + i <= 0 || y * r + j <= 0)
						continue;
					sum.s[0] += tmp[(x * r + i) * C_H + (y * r +j)].s[0];
					sum.s[1] += tmp[(x * r + i) * C_H + (y * r +j)].s[1];
					sum.s[2] += tmp[(x * r + i) * C_H + (y * r +j)].s[2];
					sum.s[3]++;
				}
			}
			i = - 1;
			while (++i < r)
			{
				j = - 1;
				while (++j < r)
				{
					if (x * r + i >= C_W || y * r + j >= C_H || x * r + i <= 0 || y * r + j <= 0)
						continue;
					z[(x * r + i)  * C_H + (y * r + j)].s[0] = sum.s[0] / sum.s[3];
					z[(x * r + i)  * C_H + (y * r + j)].s[1] = sum.s[1] / sum.s[3];
					z[(x * r + i)  * C_H + (y * r + j)].s[2] = sum.s[2] / sum.s[3];
				}
			}
			
		}
	}
	free(tmp);
}

void	sepia(cl_int4 *z)
{
	int			x;
	int			y;
	int			tmp_r;
	int			tmp_g;

	x =  - 1;	
	while (++x < C_W)
	{
		y = - 1;
		while (++y < C_H)
		{
			tmp_r = z[x * C_H + y].s[0];
			tmp_g = z[x * C_H + y].s[1];
			z[x * C_H + y].s[0] = (tmp_r * .393) + (tmp_g * .769) + (z[x * C_H + y].s[2] * .189);
			z[x * C_H + y].s[1] = (tmp_r * .349) + (tmp_g * .686) + (z[x * C_H + y].s[2] * .168);
			z[x * C_H + y].s[2] = (tmp_r * .272) + (tmp_g * .534) + (z[x * C_H + y].s[2] * .131);
		}
	}
}

void	grayscale(cl_int4 *z , int i)
{
	int			x;
	int			y;
	int			tmp_r;
	int			tmp_g;
	int			gray;

	x =  - 1;	
	while (++x < C_W)
	{
		y = - 1;
		while (++y < C_H)
		{
			tmp_r = z[x * C_H + y].s[0];
			tmp_g = z[x * C_H + y].s[1];
			gray = (tmp_r * .3) + (tmp_g * .59) + (z[x * C_H + y].s[2] * .11);
			z[x * C_H + y].s[0] = (tmp_r * (10 - i) + gray * i) / 10 ;
			z[x * C_H + y].s[1] = (tmp_g * (10 - i) + gray * i) / 10 ;
			z[x * C_H + y].s[2] = (z[x * C_H + y].s[2] * (10 - i) + gray * i) / 10 ;
		}
	}
}

void	invert(cl_int4 *z)
{
	int			x;
	int			y;

	x =  - 1;	
	while (++x < C_W)
	{
		y = - 1;
		while (++y < C_H)
		{
			z[x * C_H + y].s[0] = abs(255 - z[x * C_H + y].s[0]);
			z[x * C_H + y].s[1] = abs(255 - z[x * C_H + y].s[1]);
			z[x * C_H + y].s[2] = abs(255 - z[x * C_H + y].s[2]);
		}
	}
}

void dodge(cl_int4*	front,cl_int4*	back)
{
	int			x;
	int			y;

	x =  - 1;
	while (++x < C_W)
	{
		y = - 1;
		while (++y < C_H)
		{
			front[x * C_H + y].s[0] = back[x * C_H + y].s[0] == 255 ? 255 : \
				front[x * C_H + y].s[0] * 255 / (255 - back[x * C_H + y].s[0]);
			front[x * C_H + y].s[1] = back[x * C_H + y].s[1] == 255 ? 255 : \
				front[x * C_H + y].s[1] * 255 / (255 - back[x * C_H + y].s[1]);
			front[x * C_H + y].s[2] = back[x * C_H + y].s[2] == 255 ? 255 : \
				front[x * C_H + y].s[2] * 255 / (255 - back[x * C_H + y].s[2]);
		}
	}
}
    

void pencil(cl_int4 *z, int i) {
    cl_int4*		res;
	cl_int4*	back;

	back = (cl_int4*)malloc(sizeof(cl_int4) * C_H * C_W);
	res = (cl_int4*)malloc(sizeof(cl_int4) * C_H * C_W);
	grayscale(z, 10);
	back = ft_memcpy(back, z, sizeof(cl_int4) * C_H * C_W);
	invert(back);
	box_blur(back, i);
	dodge(z,back);
	free(back);
}

void	norm(cl_int4 *z)
{
	int			x;
	int			y;

	x =  - 1;	
	while (++x < C_W)
	{
		y = - 1;
		while (++y < C_H)
		{
			if (z[x * C_H + y].s[0] > 255)
				z[x * C_H + y].s[0] = 255;
            if (z[x * C_H + y].s[1] > 255)
				z[x * C_H + y].s[1] = 255;
            if (z[x * C_H + y].s[2] > 255)
				z[x * C_H + y].s[2] = 255;
		}
	}
}

void	effect(cl_int4 *z, t_scene scene)
{
    norm(z);
	if (scene.effect == 's')
		sepia(z);
	if (scene.effect == 'g')
		grayscale(z, scene.effect_int);
	if (scene.effect == 'b')
		box_blur(z, scene.effect_int);
	if (scene.effect == 'p')
		pixelize(z, scene.effect_int);
	if (scene.effect == 'i')
		invert(z);
	if (scene.effect == 'l')
		pencil(z, scene.effect_int);
}