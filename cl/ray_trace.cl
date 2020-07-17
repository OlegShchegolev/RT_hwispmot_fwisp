
#include "ray_trace.ch"
#include "textures.cl"
#include "slice.cl"
#include "intersect.cl"
#include "light.cl"
#include "colors.cl"

int			get_closest(t_ray od, t_object *objects, float *dist, t_lim lim)
{
	int obj;
	t_roots	t;
	int i = 0;
	float3		texture;
	t_roots	tmp;


	*dist = INF;
	obj = -1;
	t.t1 = INF;
	t.t2 = INF;
	while (i < 20)
	{
		if (objects[i].type == 's')
			t = ft_intersect_ray_sphere(od.o, od.d, objects[i]);
		if (objects[i].type == 'p')
			t = ft_intersect_ray_plane(od.o, od.d, objects[i]);
		if (objects[i].type == 'c')
			t = ft_intersect_ray_cyl(od.o, od.d, objects[i]);
		if (objects[i].type == 't')
			t = ft_intersect_ray_cone(od.o, od.d, objects[i]);
		//black inside
		
		// if ((t.t1 < -0.001 && t.t2 > 0.001) || (t.t1 > 0.001 && t.t2 < -0.001) )
		// 	return(-1);

		
		if (t.t1 < *dist && t.t1 >= lim.min && t.t1 <= lim.max)
		{
			*dist = t.t1;
			obj = i;
			tmp.t2 = t.t2;
			tmp.t1 = t.t1;
		}
		if (t.t2 < *dist && t.t2 >= lim.min && t.t2 <= lim.max)
		{
			*dist = t.t2;
			obj = i;
			tmp.t2 = t.t2;
			tmp.t1 = t.t1;
		}

		i++;
	}
	if (obj != -1 && objects[obj].negative == 1)
	{
		if (tmp.t1  > 0 &&  tmp.t2 >0)
		{
			if (tmp.t1 < tmp.t2)
				*dist = tmp.t2;
			else
				*dist = tmp.t1;
		}
		
	}
	return (obj);
}


int4		ft_trace_ray(t_ray od, t_lim lim, t_scene scene, int depth)
{
	int			closest;
	int			obj;
	t_object	tmp;
	float3		back;
	float3		tmp_o;

	back = (float3)(0.0f, 0.0f, 0.0f);
	closest = get_closest(od, scene.objects, &(tmp.dist), lim);
	
	if (closest != -1 && scene.objects[closest].negative == 1)
	{
		od.o = od.o + od.d * tmp.dist * 1.0001f;
		closest = get_closest(od, scene.objects, &(tmp.dist), lim);
	}
	// if (scene.objects[closest].negative == 1)
	// {
	// 	return ((int4)(255,0,0,0));
	// }
	// if (scene.objects[closest].type == 'c')
	// {
	// 	return ((int4)(0,255,0,0));
	// }
	// if (scene.objects[closest].type == 'p')
	// {
	// 	return ((int4)(0,0,255,0));
	// }
	obj = closest;
	if (closest == -1)
		return ((int4)(convert_int3(back), obj));
	else	
	{
		scene.objects[closest].dist = tmp.dist;
	
		back = obj_col(&od, closest, scene, depth);
		int me = closest;
			while (depth > 0)
			{
				me = closest;
				closest = get_closest(od, scene.objects, &(tmp.dist), lim);
				
				scene.objects[closest].dist = tmp.dist;
				if (closest >= 0 &&  scene.objects[me].reflective > 0)
			 		back = back * (1 - scene.objects[me].reflective) +	obj_col(&od, closest, scene, depth) * scene.objects[me].reflective ;
				else depth = 0;
			 	depth = depth - 1;
			}
	 		return ((int4)(convert_int3(back), obj));
	
	}
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
	int y_coord = work_item_id % height ;
	int x_coord = work_item_id / height ;
	int4 finalcolor;

	t_lim		lim;
	t_ray		od;
	
	lim.min = 0.0001f;
	lim.max = INF;
	
	od.o = scene.viewpoint;
	
	od.d = ft_vrot(ft_canvas_to_viewport(x_coord, y_coord, width, height), scene.rot_matrix);
	od.d = od.d / length(od.d);
	finalcolor = ft_trace_ray(od, lim, scene, 1);

	output[work_item_id] = finalcolor;
}
