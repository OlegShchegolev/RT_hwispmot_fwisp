/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 06:27:03 by hwispmot          #+#    #+#             */
/*   Updated: 2020/07/15 03:15:34 by fwisp            ###   ########.fr       */
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
# define C_H 768
# define C_D 32
# define V_W 1.
# define V_H 1.
# define N_OBJ 20
# define N_SRC 10
// # include <OpenCL/opencl.h>
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

typedef struct 			s_sdl
{
	SDL_Surface			*screen;
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Texture			*texture;
	t_cl				cl_inst;
}						t_sdl;

typedef struct			s_lim
{
	float				max;
	float				min;
}						t_lim;

typedef struct			s_matrix
{
	float				m[3][3];
}						t_matrix;

typedef struct			s_cl_object
{
	cl_char				type;
	cl_float			dist;
	cl_float3			center;
	cl_float			radius;
	cl_float3			norm;
	cl_float			alpha;
	cl_int3				color;
	cl_int				specular;
	cl_float			reflective;
	cl_int				texture;
	cl_char				textype;
	cl_float2			shift;
	cl_float2			scale;
	cl_float4			slice[4];
	cl_int				slice_side[4];
	cl_int				negative;
}						t_cl_object;

typedef struct			s_cl_source
{
	cl_float3			position;
	cl_float3			direction;
	cl_float			intensity;
	cl_char				type;
}						t_cl_source;

typedef struct			s_scene
{
	t_cl_object			objects[N_OBJ];
	t_cl_source			sources[N_SRC];
	cl_float3			startviewpoint;
	cl_float3			viewpoint;
	t_matrix			rot_matrix;
	t_lim				cl_lim;
	t_lim				tr_lim;
	cl_int				effect;
	cl_int				effect_int;
}						t_scene;	


cl_float3				return_zero_vector(void);
cl_float2				return_zero_2dvector(void);
cl_float4				return_zero_4dvector(void);
cl_int3 				return_zero_color(void);
cl_float3				parse_vector(char *str);
cl_float2				parse_2dvector(char *str);
cl_float4				parse_4dvector(char *str);
cl_int3		    		parse_color(char *str);
char					parse_type(char *str);
void					get_slices(t_cl_object *object, char *str0);
void					get_object_parameters(t_cl_object *object, char *str);
char					parse_object_type(char *str);
void					check_sources(t_cl_source *sources);
cl_int3					*rt_cl(t_cl *cl, t_scene scene);
cl_float3				ft_vrot(cl_float3, t_matrix rot);
t_scene					construct_scene(char *str);
cl_int4					*ft_draw(t_sdl sdl, t_scene scene);
void					effect(cl_int4 *z, t_scene scene);
t_matrix				return_eig_rot_m(cl_float3 cam_ang);
t_cl					initcl(void);
void					set_ker_arg(t_cl *cl);
void					ft_parse_scene(char *filename, t_scene *scene);
#endif
