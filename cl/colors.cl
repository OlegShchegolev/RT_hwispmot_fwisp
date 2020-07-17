
float3		cone_col(t_ray *p_od, int closest, t_scene scene, int depth)
{
	float3		back;
	t_ray		pr;
	float		reflection;
	t_ray		od = *p_od;

	pr.o = od.o + (od.d * scene.objects[closest].dist);
	pr.d = pr.o - scene.objects[closest].center;
	pr.d = cross((scene.objects[closest].norm * dot(scene.objects[closest].norm, pr.d)), pr.d);
	pr.d = cross(pr.d, (pr.o - scene.objects[closest].center));
	pr.d = pr.d * (1.0f / length(pr.d));

	back = convert_float3(scene.objects[closest].color);
	if (scene.objects[closest].texture > 0)
	 	back = gtexture(scene.objects[closest], pr.d, pr.o);

	back = back * compute_lighting(pr, (od.d * (-1)), scene, scene.objects[closest].specular, closest);

	od.d = - od.d;
	pr.d = pr.d * (2.0f * dot(pr.d, od.d)) - od.d;
	pr.d = pr.d /length(pr.d);
	*p_od = pr;
	return (back);
}

float3		cyl_col(t_ray *p_od, int closest, t_scene scene, int depth)
{
	float3		back;
	t_ray		pr;
	float		reflection;
	t_ray		od = *p_od;

	pr.o = od.o + (od.d * scene.objects[closest].dist);
	pr.d = pr.o - scene.objects[closest].center;
	pr.d = cross(pr.d, scene.objects[closest].norm);
	pr.d = cross(scene.objects[closest].norm, pr.d);
	pr.d = pr.d * (1.0f / length(pr.d));

	back = convert_float3(scene.objects[closest].color);
	if (scene.objects[closest].texture > 0)
	 	back = gtexture(scene.objects[closest], pr.d, pr.o);

	back = back * compute_lighting(pr, (od.d * (-1)), scene, scene.objects[closest].specular, closest);
	od.d = - od.d;
	pr.d = pr.d * (2.0f * dot(pr.d, od.d)) - od.d;
	pr.d = pr.d /length(pr.d);
	*p_od = pr;
	return(back);
}

float3		plane_col(t_ray *p_od, int closest, t_scene scene, int depth)
{
	float3		back;
	t_ray		pr;
	float		reflection;
	t_ray		od = *p_od;

	pr.o = od.o + (od.d * scene.objects[closest].dist);
	pr.d = - scene.objects[closest].norm;
	pr.d = pr.d * (1.0f / length(pr.d));

	back = convert_float3(scene.objects[closest].color);
	if (scene.objects[closest].texture > 0)
	 	back = gtexture(scene.objects[closest], pr.d, pr.o);

	back = back * compute_lighting(pr, (od.d * (-1)), scene, scene.objects[closest].specular, closest);
	
	od.d = - od.d ;
	pr.d = pr.d * (2.0f * dot(pr.d, od.d)) - od.d;
	pr.d = pr.d /length(pr.d);
	*p_od = pr;
	return(back);
}

float3		sphere_col(t_ray *p_od, int closest, t_scene scene, int depth)
{
	float3		back;
	t_ray		pr;
	float		reflection;
	t_ray		od = *p_od;
	float3		texture;
	float3		norm;

	pr.o = od.o + (od.d * scene.objects[closest].dist);
	pr.d = pr.o - (scene.objects[closest].center);
	norm = pr.d * (1.0f / length(pr.d));

	back = convert_float3(scene.objects[closest].color);

	if (scene.objects[closest].texture > 0 && (scene.objects[closest].textype == 'c'))
	 	back = gtexture(scene.objects[closest], norm, pr.o);
	
	if (scene.objects[closest].textype == 'b')
	{
		texture = gtexture(scene.objects[closest], norm, pr.o);
		od.d = normalize(od.d) + normalize(cross(od.d, (float3)(1.0f, 0.0f, 0.0f))) * (texture.x / 255) + normalize(cross(od.d, (float3)(0.0f, 1.0f, 0.0f))) * (texture.y / 255);
	}

	back = back * compute_lighting(pr, (od.d * (-1)), scene, scene.objects[closest].specular, closest);
	od.d = od.d * (-1);
	pr.d = pr.d * (2.0f * dot(pr.d, od.d)) - od.d;
	pr.d = pr.d /length(pr.d);
	*p_od = pr;
	return (back);
}

float3		obj_col(t_ray *p_od, int closest, t_scene scene, int depth)
{
	float3		back;

	back = (float3)(0.0f, 0.0f, 120.0f);
	if (scene.objects[closest].type == 's')
		back = sphere_col(p_od, closest, scene, depth);
	if (scene.objects[closest].type == 'p')
		back = plane_col(p_od, closest, scene, depth);
	if (scene.objects[closest].type == 'c')
		back = cyl_col(p_od, closest, scene, depth);
	if (scene.objects[closest].type == 't')
		back = cone_col(p_od, closest, scene, depth);
	return (back);
}