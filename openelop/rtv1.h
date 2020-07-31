/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 06:27:03 by hwispmot          #+#    #+#             */
/*   Updated: 2020/01/28 21:41:10 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "SDL.h"
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft.h"
# define DMAX 4000000
# define C_W 1024
# define C_H 1024
# define C_D 32
# define V_W 1.
# define V_H 1.
# define PI 3.1415926
# define CL_TARGET_OPENCL_VERSION 120
# include <CL/opencl.h>
# include <CL/cl.h>

typedef struct			s_cl
{
	char				*source_str;
	size_t				source_size;
	cl_context			context;
	cl_device_id		dev_id;
	cl_platform_id		platform_id;
	cl_program			program;
	cl_command_queue	command_queue;
	cl_kernel			kernel;
	cl_mem				z_clmem;
	cl_mem				scene_buf;
}						t_cl;

typedef struct s_sdl
{
	SDL_Surface		*screen;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	t_cl			cl_inst;
}				t_sdl;

typedef struct	s_lim
{
	float	max;
	float	min;
}				t_lim;

////////////////////////////
typedef struct	s_vector
{
	float	x;
	float	y;
	float	z;
}				t_vector;
///////////////////////////

typedef struct	s_od
{
	t_vector	o;
	t_vector	d;
}				t_od;

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct	s_sphere
{
	t_vector	center;
	float		radius;
	t_color		color;
	int			specular;
	float		reflective;
}				t_sphere;

typedef struct	s_plane
{
	t_vector	center;
	t_vector	norm;
	t_color		color;
	int			specular;
	float		reflective;
}				t_plane;

typedef struct	s_cyl
{
	t_vector	pa;
	t_vector	va;
	float		radius;
	t_color		color;
	int			specular;
	float		reflective;
}				t_cyl;

typedef struct	s_cone
{
	t_vector	pa;
	t_vector	va;
	float		alpha;
	t_color		color;
	int			specular;
	float		reflective;
}				t_cone;

typedef struct	s_object
{
	char		type;
	void		*obj;
	float		dist;
}				t_object;

// typedef struct	s_source
// {
// 	t_vector	position;
// 	float		intensity;
// 	char		type;
// 	t_vector	intensities;
// }				t_source;

typedef struct	s_params
{
	float	t1;
	float	t2;
}				t_params;

typedef struct	s_matrix
{
	float		m[3][3];
}				t_matrix;

typedef struct	s_cl_object
{
	cl_char		type;
	cl_float		dist;
	cl_float3		center;
	cl_float		radius;
	cl_float3		norm;
	cl_float	alpha; //cone
	
	cl_int3		color;
	cl_int			specular;
	cl_float		reflective;
	cl_int		texture;
	cl_char		textype;
	cl_float2		shift;
	cl_float2		scale;


	cl_float			refractive;
	//добавить
}				t_cl_object;

typedef struct	s_cl_source
{
	cl_float3		position;
	cl_char			type;

	//заменить
	cl_float3		intensities;
}				t_cl_source;

typedef struct	s_scene
{
	t_cl_object	objects[20];
	t_cl_source	sources[10];
	cl_float3	startviewpoint;
	cl_float3	viewpoint;
	t_matrix	rot_matrix;
	t_lim		cl_lim;
	t_lim		tr_lim;
	cl_float3	cam_ang;
}				t_scene;	



cl_int3			*rt_cl(t_cl *cl, t_scene scene);

cl_float3		ft_vrot(cl_float3, t_matrix rot);


t_vector		ft_canvas_to_viewport(int x, int y);
t_color			ft_trace_ray(t_od od, t_lim lim, t_scene scene, int depth);
t_scene			construct_scene(char *str);
cl_int4			*ft_draw(t_sdl sdl, t_scene scene);



t_matrix	return_eig_rot_m(cl_float3 cam_ang);

t_cl	initcl(void);
void	set_ker_arg(t_cl *cl);

#endif
