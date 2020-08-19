#include "cl/ray_trace.h"

t_ray		obj_refl(t_ray od, t_ray pr, int closest, t_scene scene)
{
	
	od.d = apply_bump(od, scene.objects[closest], scene.objects[closest].dist);
	
	od.d = od.d * (-1);
	pr.d = pr.d * (2.0f * dot(pr.d, od.d)) - od.d;
	pr.d = normalize(pr.d);
	return (pr);
}

t_ray		obj_refr(t_ray od, int closest, t_scene scene)
{
	t_ray		pr;
	t_ray		refr;
	float		tetta_1;
	float		n_dot_i;

	float3		normal;
	float3		i;

	float		eta;
	float		etai;
	float		etat;


	// get normal
	if (scene.objects[closest].type == 's')
	{
		pr.o = od.o + (od.d * scene.objects[closest].dist);
		pr.d = pr.o - (scene.objects[closest].center);
		// norm = pr.d * (1.0f / length(pr.d));
		pr.d = pr.d * (1.0f / length(pr.d));
		// if (scene.objects[closest].textype == 'b')
		// {
		// 	texture = gtexture(scene.objects[closest], norm, pr.o);
		// 	od.d = normalize(od.d) + normalize(cross(od.d, (float3)(1.0f, 0.0f, 0.0f))) * (texture.x / 255) + normalize(cross(od.d, (float3)(0.0f, 1.0f, 0.0f))) * (texture.y / 255);
		// }
	}
	if (scene.objects[closest].type == 'p')
	{
		pr.o = od.o + (od.d * scene.objects[closest].dist);
		pr.d = scene.objects[closest].norm;
		pr.d = pr.d * (1.0f / length(pr.d));
	}

	if (scene.objects[closest].type == 'c')
	{
		pr.o = od.o + (od.d * scene.objects[closest].dist);
		pr.d = pr.o - scene.objects[closest].center;
		pr.d = cross(pr.d, scene.objects[closest].norm);
		pr.d = cross(scene.objects[closest].norm, pr.d);
		pr.d = pr.d * (1.0f / length(pr.d));
	}
	if (scene.objects[closest].type == 't')
	{
		pr.o = od.o + (od.d * scene.objects[closest].dist);
		pr.d = pr.o - scene.objects[closest].center;
		pr.d = cross((scene.objects[closest].norm * dot(scene.objects[closest].norm, pr.d)), pr.d);
		pr.d = cross(pr.d, (pr.o - scene.objects[closest].center));
		pr.d = pr.d * (1.0f / length(pr.d));
	}


	// set normal
	normal = pr.d;

	// crossing point
	refr.o = pr.o; //od.o + (od.d * scene.objects[closest].dist);

	// incident ray
	i = od.d;


	n_dot_i = dot(normal, i);

	etai = 1;
	etat = scene.objects[closest].index_of_refr;

	if (n_dot_i < 0)
	{
		n_dot_i = -n_dot_i;
		eta = etai / etat;
	}
	else
	{
		pr.d = -pr.d;
		eta = etat / etai;
	}


	// 1st angle (incident angle)
	tetta_1 = acos(dot(normal, i) / (length(normal) * length(i)));


	// refr ray dir
	refr.d = eta * (i + cos(tetta_1) * normal) -\
		normal * sqrt(1 - eta * eta * sin(tetta_1) * sin(tetta_1));


	return (refr);
}