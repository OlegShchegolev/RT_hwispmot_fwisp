#include "cl/ray_trace.h"

float3		get_intersection_p(t_ray od, int closest, t_scene scene)
{
	return (od.o + (od.d * scene.objects[closest].dist));
}

float3		get_normal(t_ray od, int closest, t_scene scene)
{
	float3		normal;
	float3		intrs_p;

	intrs_p = get_intersection_p(od, closest, scene);
	if (scene.objects[closest].type == 's')
	{
		normal = intrs_p - scene.objects[closest].center;
		normal = normal * (1.0f / length(normal));
	}
	if (scene.objects[closest].type == 'p')
	{
		normal = intrs_p - scene.objects[closest].center;
		normal = cross(normal, scene.objects[closest].norm);
		normal = cross(scene.objects[closest].norm, normal);
		normal = normal * (1.0f / length(normal));
	}

	if (scene.objects[closest].type == 'c')
	{
		normal = intrs_p - scene.objects[closest].center;
		normal = cross(normal, scene.objects[closest].norm);
		normal = cross(scene.objects[closest].norm, normal);
		normal = normal * (1.0f / length(normal));
	}
	if (scene.objects[closest].type == 't')
	{
		normal = intrs_p - scene.objects[closest].center;
		normal = cross((scene.objects[closest].norm * dot(scene.objects[closest].norm, normal)), normal);
		normal = cross(normal, (intrs_p - scene.objects[closest].center));
		normal = normal * (1.0f / length(normal));
	}
	return (normal);
}

t_ray		obj_refl(t_ray od, int closest, t_scene scene)
{
	float3		texture;
	float3		normal;
	t_ray		refl_ray;


	refl_ray.o = get_intersection_p(od, closest, scene);//od.o + (od.d * scene.objects[closest].dist);
	normal = get_normal(od, closest, scene);

	if (scene.objects[closest].type == 's')
	{
		if (scene.objects[closest].textype == 'b')
		{
			texture = gtexture(scene.objects[closest], normal, refl_ray.o);
			od.d = normalize(od.d) + normalize(cross(od.d, (float3)(1.0f, 0.0f, 0.0f))) * (texture.x / 255) + normalize(cross(od.d, (float3)(0.0f, 1.0f, 0.0f))) * (texture.y / 255);
		}
	}
	
	od.d = od.d * (-1);
	refl_ray.d = normal * (2.0f * dot(normal, od.d)) - od.d;
	refl_ray.d = refl_ray.d /length(refl_ray.d);
	return (refl_ray);
}

// t_ray		obj_refl(t_ray od, int closest, t_scene scene)
// {
// 	t_ray		pr;
// 	float3		texture;
// 	float3		norm;

// 	if (scene.objects[closest].type == 's')
// 	{
// 		pr.o = od.o + (od.d * scene.objects[closest].dist);
// 		pr.d = pr.o - (scene.objects[closest].center);
// 		norm = pr.d * (1.0f / length(pr.d));
// 		if (scene.objects[closest].textype == 'b')
// 		{
// 			texture = gtexture(scene.objects[closest], norm, pr.o);
// 			od.d = normalize(od.d) + normalize(cross(od.d, (float3)(1.0f, 0.0f, 0.0f))) * (texture.x / 255) + normalize(cross(od.d, (float3)(0.0f, 1.0f, 0.0f))) * (texture.y / 255);
// 		}
// 	}
// 	if (scene.objects[closest].type == 'p')
// 	{
// 		pr.o = od.o + (od.d * scene.objects[closest].dist);
// 		pr.d = pr.o - scene.objects[closest].center;
// 		pr.d = cross(pr.d, scene.objects[closest].norm);
// 		pr.d = cross(scene.objects[closest].norm, pr.d);
// 		pr.d = pr.d * (1.0f / length(pr.d));
// 	}

// 	if (scene.objects[closest].type == 'c')
// 	{
// 		pr.o = od.o + (od.d * scene.objects[closest].dist);
// 		pr.d = pr.o - scene.objects[closest].center;
// 		pr.d = cross(pr.d, scene.objects[closest].norm);
// 		pr.d = cross(scene.objects[closest].norm, pr.d);
// 		pr.d = pr.d * (1.0f / length(pr.d));
// 	}
// 	if (scene.objects[closest].type == 't')
// 	{
// 		pr.o = od.o + (od.d * scene.objects[closest].dist);
// 		pr.d = pr.o - scene.objects[closest].center;
// 		pr.d = cross((scene.objects[closest].norm * dot(scene.objects[closest].norm, pr.d)), pr.d);
// 		pr.d = cross(pr.d, (pr.o - scene.objects[closest].center));
// 		pr.d = pr.d * (1.0f / length(pr.d));
// 	}
// 	od.d = od.d * (-1);
// 	pr.d = pr.d * (2.0f * dot(pr.d, od.d)) - od.d;
// 	pr.d = pr.d /length(pr.d);
// 	return (pr);
// }

t_ray		obj_refr(t_ray od, int closest, t_scene scene)
{
	t_ray		refr_ray;
	float		tetta_1;
	float		n_dot_i;
	float3		normal;
	float3		i;
	float		eta;
	float		etai;
	float		etat;
	float		k;


	// set indexs of refraction
	etai = 1;
	etat = scene.objects[closest].index_of_refr;

	// get intersect_point
	refr_ray.o = get_intersection_p(od, closest, scene);//od.o + (od.d * scene.objects[closest].dist);

	// get normal
	normal = get_normal(od, closest, scene);

	// incident ray
	i = od.d;


	n_dot_i = dot(normal, i);

	

	if (n_dot_i < 0)
	{
		// we are outside the surface, we want cos(theta) to be positive
		n_dot_i = -n_dot_i;
		eta = etai / etat;
	}
	else
	{
		// we are inside the surface, cos(theta) is already positive but reverse normal direction
		normal = -normal;
		eta = etat / etai;
	}


	// 1st angle (incident angle)
	tetta_1 = acos(dot(normal, i) / (length(normal) * length(i)));


	// refr_ray dir
	refr_ray.d = eta * (i + cos(tetta_1) * normal) -\
		normal * sqrt(1 - eta * eta * sin(tetta_1) * sin(tetta_1));


	return (refr_ray);
}