#include "rtv1.h"

void vector_div_n(cl_int4* z, int n)
{
	z->s0 /= n;
	z->s1 /= n;
	z->s2 /= n;
}

void vector_sum(cl_int4* z, cl_int4 add)
{
	z->s0 += add.s0;
	z->s1 += add.s1;
	z->s2 += add.s2;
	z->s3++;
}

cl_int4 ret_vector_div_n(cl_int4 a, int n)
{
	cl_int4	b;

	b.s0 = a.s0 / n;
	b.s1 = a.s1 / n;
	b.s2 = a.s2 / n;
	return (b);
}

void box_blur(cl_int4 *z, int n)
{
    cl_int4		sum;
	int			d[2];
	int			i[2];
	
	d[0] =  -1;	
	while (++d[0] < C_W)
	{
		d[1] = - 1;
		while (++d[1] < C_H)
		{
			sum = (cl_int4){{0, 0, 0, 1}};
			i[0] = -n - 1;
			while (++i[0] < n + 1)
			{
				i[1] = -n - 1;
				while (++i[1] < n + 1)
					if (d[0] + i[0] < C_W && d[1] + i[1] < C_H \
							&& d[0] + i[0] > 0 && d[1] + i[1] > 0)
						vector_sum(&sum, z[(d[0] + i[0]) * C_H + (d[1] + i[1])]);
			}
			z[d[0] * C_H + d[1]] = ret_vector_div_n(sum, sum.s[3]);
		}
	}
}

void	make_pixelize(int *c, int n, cl_int4 *z, cl_int4 sum)
{
	int		i[2];

	i[0] = - 1;
	while (++i[0] < n)
	{
		i[1] = - 1;
		while (++i[1] < n)
			if (c[0] * n + i[0] < C_W && c[1] * n + i[1] < C_H && \
								c[0] * n + i[0] > 0 && c[1] * n + i[1] > 0)
				z[(c[0] * n + i[0])  * C_H + (c[1] * n + i[1])] = ret_vector_div_n(sum, sum.s3);
	}
}

void pixelize(cl_int4 *z, int n)
{
    cl_int4		sum;
	int			c[2];
	int			i[2];
	
	c[0] =  - 1;	
	while (++c[0] * n < C_W)
	{
		c[1] = - 1;
		while (++c[1] * n < C_H)
		{
			sum = (cl_int4){{0, 0, 0, 1}};
			i[0] = - 1;
			while (++i[0] < n + 1)
			{
				i[1] = - 1;
				while (++i[1] < n + 1)
					if (c[0] * n + i[0] < C_W && c[1] * n + i[1] < C_H && \
									c[0] * n + i[0] > 0 && c[1] * n + i[1] > 0)
						vector_sum(&sum, z[(c[0] * n + i[0]) * C_H + (c[1] * n +i[1])]);
			}
			make_pixelize(c, n, z, sum);
		}
	}
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

void	three_d(t_sdl sdl, t_scene scene, cl_int4 *z)
{
		cl_int4		*z_add;
		int			i;

		scene.viewpoint.s0 += 0.1;
		z_add = rt_cl(&(sdl.cl_inst), scene);
		i = -1;
		while (++i < C_W * C_H)
		{
				z[i].s[1] = z_add[i].s[1];
				z[i].s[2] = z_add[i].s[2];
		}
		free(z_add);
}

void	antialiasing(cl_int4* z, int n)
{
	int		i;
	int		j;
	int		x;
	int		y;

	x = 0;	
	while (x < C_W * n)
	{
		y = 0;
		while (y < C_H * n)
		{
			i = -1;
			z[x / n * C_H + y / n] = (cl_int4){{0, 0, 0, 0}};
			while (++i < n)
			{
				j = -1;
				while (++j < n)
					vector_sum(z + x / n * C_H + y / n, z[((x + i) * n) * C_H + y + j]);
			}
			vector_div_n(z + x / n * C_H + y / n, pow(n, 2));
			y += n;
		}
		x += n;
	}
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

void	effect(cl_int4 *z, t_sdl sdl, t_scene scene)
{
    norm(z);
	if (scene.effect == 's')
		sepia(z);
	else if (scene.effect == 'g')
		grayscale(z, scene.effect_int);
	else if (scene.effect == 'b')
		box_blur(z, scene.effect_int);
	else if (scene.effect == 'p')
		pixelize(z, scene.effect_int);
	else if (scene.effect == 'i')
		invert(z);
	else if (scene.effect == 'l')
		pencil(z, scene.effect_int);
	else if (scene.effect == 't')
		three_d(sdl, scene, z);
	else if (scene.effect == 'a')
		antialiasing(z, scene.effect_int);
}