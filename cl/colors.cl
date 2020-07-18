float3		obj_col(t_ray od, int closest, t_scene scene, t_ray *r1, float3 *f1)
{
	float3		back;
	t_ray		pr;
	float3		texture;
	float3		norm;

	if (scene.objects[closest].type == 's')
	{
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
	}
	if (scene.objects[closest].type == 'p')
	{
		pr.o = od.o + (od.d * scene.objects[closest].dist);
		pr.d = - scene.objects[closest].norm;
		pr.d = pr.d * (1.0f / length(pr.d));

		back = convert_float3(scene.objects[closest].color);
		if (scene.objects[closest].texture > 0)
			back = gtexture(scene.objects[closest], pr.d, pr.o);
	}
	if (scene.objects[closest].type == 'c')
	{
		pr.o = od.o + (od.d * scene.objects[closest].dist);
		pr.d = pr.o - scene.objects[closest].center;
		pr.d = cross(pr.d, scene.objects[closest].norm);
		pr.d = cross(scene.objects[closest].norm, pr.d);
		pr.d = pr.d * (1.0f / length(pr.d));

		back = convert_float3(scene.objects[closest].color);
		if (scene.objects[closest].texture > 0)
			back = gtexture(scene.objects[closest], pr.d, pr.o);
	}
	if (scene.objects[closest].type == 't')
	{
		pr.o = od.o + (od.d * scene.objects[closest].dist);
		pr.d = pr.o - scene.objects[closest].center;
		pr.d = cross((scene.objects[closest].norm * dot(scene.objects[closest].norm, pr.d)), pr.d);
		pr.d = cross(pr.d, (pr.o - scene.objects[closest].center));
		pr.d = pr.d * (1.0f / length(pr.d));

		back = convert_float3(scene.objects[closest].color);
		if (scene.objects[closest].texture > 0)
			back = gtexture(scene.objects[closest], pr.d, pr.o);
	}
	
	*r1 = pr;
	*f1 = -od.d;
	return (back);
}