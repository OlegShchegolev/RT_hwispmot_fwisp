
#include "rtv1.h"

void	init_program_names(char *header[], char *programs[], t_cl *cl)
{
	int		fd;

	header[0] = "cl/ray_trace.h";
	programs[0] = "cl/ray_trace.cl";
	programs[1] = "cl/colors.cl";
	programs[2] = "cl/intersect.cl";
	programs[3] = "cl/light.cl";
	programs[4] = "cl/reflection.cl";
	programs[5] = "cl/slice.cl";
	programs[6] = "cl/textures.cl";
	fd = open(header[0], O_RDONLY);
	cl->source_str = (char*)malloc(10000000);
	cl->source_size = read(fd, cl->source_str, 10000000);
	close(fd);
	cl->header[0] = clCreateProgramWithSource(cl->context, 1,
	(const char **)&cl->source_str, (const size_t *)&cl->source_size, NULL);
	free(cl->source_str);
}

void	progress_bar(t_sdl *sdl, int x, int y, int w, int h, float Percent)
{
   Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : Percent;
   SDL_Color old;
   SDL_GetRenderDrawColor(sdl->renderer, &old.r, &old.g, &old.g, &old.a);
   SDL_Rect bgrect = { x, y, w, h };
   SDL_SetRenderDrawColor(sdl->renderer, 255, 255, 255, 255);
   SDL_RenderFillRect(sdl->renderer, &bgrect);
   SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, 255);
   int pw = (int)((float)w * Percent);
   int px = x + (w - pw);
   SDL_Rect fgrect = { px, y, pw, h };
   //SDL_RenderFillRect(sdl->renderer, &fgrect);
   SDL_SetRenderDrawColor(sdl->renderer, old.r, old.g, old.b, old.a);
}

void	compile_cl(t_cl *cl)
{
	char* header[1];
	char* programs[7];
	int			fd;
	int			i;

	init_program_names(header, programs, cl);
	i = -1;
	while (++i < 7)
	{
		fd = open(programs[i], O_RDONLY);
		cl->source_str = (char*)malloc(10000000);
		ft_memset(cl->source_str, 0,   10000000);
		cl->source_size = read(fd, cl->source_str, 10000000);
		close(fd);
		cl->programs[i] = clCreateProgramWithSource(cl->context, 1,
		(const char **)&cl->source_str, (const size_t *)&cl->source_size, NULL);
		free(cl->source_str);
		clCompileProgram(cl->programs[i], 1, &cl->dev_id,	"-Werror", 1, cl->header, (const char**)header, NULL, NULL);
	}
	cl->program = clLinkProgram(cl->context, 1, &cl->dev_id, NULL, 7, cl->programs, NULL, NULL, NULL);
}

t_cl	initcl()
{
	t_cl		cl;
	cl_uint		rnd;
	cl_uint		ret_num_platforms;
	
	clGetPlatformIDs(1, &cl.platform_id, &ret_num_platforms);
	clGetDeviceIDs(cl.platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &cl.dev_id, &rnd);
	cl.context = clCreateContext(NULL, 1, &cl.dev_id, NULL, NULL, NULL);
	cl.command_queue = clCreateCommandQueue(cl.context, cl.dev_id, 0, NULL);
	compile_cl(&cl);
	
	// {
	// 	size_t log_size;
	// 	clGetProgramBuildInfo(cl.program, cl.dev_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
	// 	char *log = (char *)malloc(log_size);
	// 	clGetProgramBuildInfo(cl.program, cl.dev_id, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
	// 	printf("log: %s\n", log);
	// 	free(log);
	// }
	// printf("link ok\n");
	cl.z_clmem = clCreateBuffer(cl.context, CL_MEM_WRITE_ONLY,
		16 * C_H * C_W * sizeof(cl_int4), NULL, NULL);	
	cl.kernel = clCreateKernel(cl.program, "render", NULL);
    return (cl);
}

void	releasecl(t_cl *cl)
{
	clReleaseMemObject(cl->z_clmem);
	clReleaseKernel (cl->kernel);
	clReleaseProgram (cl->program);
	clReleaseCommandQueue (cl->command_queue);
	clReleaseContext (cl->context);
}

cl_int3		*rt_cl(t_cl *cl, t_scene scene)
{
	cl_int4			*z;
	size_t		global_item_size;
	size_t		local_item_size;

	global_item_size = C_H * C_W;
	if (scene.effect == 'a')
	{
		scene.width *= scene.effect_int;
		scene.height *= scene.effect_int;
		global_item_size *= pow(scene.effect_int, 2);
	}
	local_item_size = 256;
	z = (cl_int4 *)malloc(sizeof(cl_int4) * global_item_size);
	clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), (void *)&cl->z_clmem);
	clSetKernelArg(cl->kernel, 1, sizeof(t_scene), &(scene));
	clEnqueueNDRangeKernel(cl->command_queue, cl->kernel, 1, NULL,
			&global_item_size, &local_item_size, 0, NULL, NULL);
	clEnqueueReadBuffer(cl->command_queue, cl->z_clmem, CL_TRUE, 0,
			global_item_size * sizeof(cl_int4), z, 0, NULL, NULL);
	clFlush(cl->command_queue);
	clFinish(cl->command_queue);
	return (z);
}