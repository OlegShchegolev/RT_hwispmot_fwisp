
#include "ray_trace.ch"
#include "textures.cl"
#include "slice.cl"
#include "intersect.cl"
#include "light.cl"
#include "colors.cl"
#include "reflection.cl"

int			get_closest(t_ray od, t_object *objects, float *dist, t_lim lim)
{
	int obj;
	t_roots	roots;
	int i = 0;
	float3		texture;
	t_roots	tmp;

	*dist = INF;
	obj = -1;
	roots.root1 = INF;
	roots.root2 = INF;
	while (i < 20)
	{
		if (objects[i].type == 's')
			roots = ft_intersect_ray_sphere(od.o, od.d, objects[i]);
		if (objects[i].type == 'p')
			roots = ft_intersect_ray_plane(od.o, od.d, objects[i]);
		if (objects[i].type == 'c')
			roots = ft_intersect_ray_cyl(od.o, od.d, objects[i]);
		if (objects[i].type == 't')
			roots = ft_intersect_ray_cone(od.o, od.d, objects[i]);
		//black inside
		
		// if ((t.root1 < -0.001 && t.root2 > 0.001) || (t.root1 > 0.001 && t.root2 < -0.001) )
		// 	return(-1);

		
		if (roots.root1 < *dist && roots.root1 >= lim.min && roots.root1 <= lim.max)
		{
			*dist = roots.root1;
			obj = i;
			tmp.root2 = roots.root2;
			tmp.root1 = roots.root1;
		}
		if (roots.root2 < *dist && roots.root2 >= lim.min && roots.root2 <= lim.max)
		{
			*dist = roots.root2;
			obj = i;
			tmp.root2 = roots.root2;
			tmp.root1 = roots.root1;
		}

		i++;
	}
	if (obj != -1 && objects[obj].negative == 1)
	{
		if (tmp.root1  > 0 &&  tmp.root2 > 0)
		{
			if (tmp.root1 < tmp.root2)
				*dist = tmp.root2;
			else
				*dist = tmp.root1;
		}
		
	}
	return (obj);
}

int4		ft_trace_ray(t_ray od, t_lim lim, t_scene scene, int depth)
{
	int			closest;
	float		dist;
	float3		back;
	float3		tmp_o;
	t_ray		od2;

	back = (float3)(0.0f, 0.0f, 0.0f);
	closest = get_closest(od, scene.objects, &(dist), lim);
	if (closest == -1)
		return ((int4)(convert_int3(back), closest));
	if (scene.objects[closest].negative == 1)
	{
		od.o = od.o + od.d * dist * 1.001f;
		closest = get_closest(od, scene.objects, &(dist), lim);
	}
	else if (scene.objects[closest].transparency > 0)
	{
		od.o = od.o + od.d * dist * 1.001f;
		back = obj_col(od, closest, scene) * (1 - scene.objects[closest].transparency);
		closest = get_closest(od, scene.objects, &(dist), lim);
	}
	if (closest == -1)
		return ((int4)(convert_int3(back), closest));
	scene.objects[closest].dist = dist;
	back = obj_col(od, closest, scene);
	od2 = obj_refl(od, closest, scene);
	int obj = closest;
	// while (depth > 0)
	// {
	// 	int me = closest;
	// 	closest = get_closest(od, scene.objects, &(dist), lim);
		
	// 	scene.objects[closest].dist = dist;
	// 	if (closest >= 0 &&  scene.objects[me].reflective > 0) {
	//  		back = back * (1 - scene.objects[me].reflective) +	obj_col(od, closest, scene) * scene.objects[me].reflective ;
	// 		od = obj_refl(od, closest, scene);
	// 	}
	// 	else depth = 0;
	//  	depth = depth - 1;
	// }
	return ((int4)(convert_int3(back), obj));
}

float3		ft_vrot(float3 a, t_matrix rot)
{
	float3	res;

	res.x = rot.m[0][0] * a.x + rot.m[0][1] * a.y + rot.m[0][2] * a.z;
	res.y = rot.m[1][0] * a.x + rot.m[1][1] * a.y + rot.m[1][2] * a.z;
	res.z = rot.m[2][0] * a.x + rot.m[2][1] * a.y + rot.m[2][2] * a.z;
	return (res);
}

float3		ft_canvas_to_viewport(int x, int y, int width, int height)
{
	float3	viewport;
	int		min;

	if (width < height)
		min = width;
	else
		min = height;
	viewport.x = (1.0f / min) * x - 0.5f / min * width;
	viewport.y = - (1.0f / min) * y + 0.5f / min * height;
	viewport.z = 1.0f;
	return (viewport);
}

__kernel void render(__global int4 *output, int width, int height, t_scene scene)
{
	int work_item_id = get_global_id(0);
	int y_coord = work_item_id % scene.height ;
	int x_coord = work_item_id / scene.height ;
	int4 finalcolor;

	t_lim		lim;
	t_ray		od;
	
	lim.min = 0.0001f;
	lim.max = INF;
	
	od.o = scene.viewpoint;
	
	od.d = ft_vrot(ft_canvas_to_viewport(x_coord, y_coord, scene.width, scene.height), scene.rot_matrix);
	od.d = od.d / length(od.d);
	finalcolor = ft_trace_ray(od, lim, scene, 1);

	output[work_item_id] = finalcolor;
}
