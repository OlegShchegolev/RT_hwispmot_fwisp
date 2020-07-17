
t_roots	ft_intersect_ray_cone(float3 o, float3 d, t_object cone)
{
	float3	dp;
	float3	k;
	float		disc;
	t_roots	t;

	dp = o - cone.center;
	k.x = pow(cos(cone.alpha), 2.0f) * dot((d - (cone.norm * dot(d, cone.norm))), (d - (cone.norm * dot(d, cone.norm)))) - pow(sin(cone.alpha) * dot(d, cone.norm), 2.0f);
	k.y = 2.0f * pow(cos(cone.alpha), 2.0f) * dot((d - (cone.norm * dot(d, cone.norm))), (dp - (cone.norm * dot(dp, cone.norm)))) - 2.0f * pow(sin(cone.alpha), 2.0f) * dot(d, cone.norm) * dot(dp, cone.norm);
	k.z = pow(cos(cone.alpha), 2.0f) * dot((dp - (cone.norm * dot(dp, cone.norm))), (dp -(cone.norm * dot(dp, cone.norm)))) - pow(sin(cone.alpha) * dot(dp, cone.norm), 2.0f);
	disc = k.y * k.y - 4.0f * k.x * k.z;
	if (disc < 0)
	{
		t.t1 = INF;
		t.t2 = INF;
		return (t);
	}
	t.t1 = (-k.y + sqrt(disc)) / (2 * k.x);
	t.t2 = (-k.y - sqrt(disc)) / (2 * k.x);
	slicer(cone, &t,	o, d);
	return (t);
}

t_roots	ft_intersect_ray_cyl(float3 o, float3 d, t_object cyl)
{
	float3	dp;
	float3	k;
	float		disc;
	t_roots	t;
	t_ray		pr;
	float3	texture;

	dp = o - cyl.center;
	k.x = dot((d - (cyl.norm * dot(d, cyl.norm))), (d - (cyl.norm * dot(d, cyl.norm))));
	k.y = 2.0f * dot((d - (cyl.norm * dot(d, cyl.norm))), (dp - (cyl.norm * dot(dp, cyl.norm))));
	k.z = dot((dp - (cyl.norm * dot(dp, cyl.norm))), (dp - (cyl.norm * dot(dp, cyl.norm)))) - cyl.radius * cyl.radius;
	disc = k.y * k.y - 4.0f * k.x * k.z;
	if (disc < 0)
	{
		t.t1 = INF;
		t.t2 = INF;
		return (t);
	}
	t.t1 = (-k.y + sqrt(disc)) / (2.0f * k.x);
	t.t2 = (-k.y - sqrt(disc)) / (2.0f * k.x);

	if (cyl.textype == 'o')
	{
		pr.o = o + (d * (t.t1));
		pr.d = pr.o - (cyl.center);
		pr.d = cross(pr.d, cyl.norm);
		pr.d = cross(cyl.norm, pr.d);
		pr.d = pr.d * (1.0f / length(pr.d));

		texture = gtexture(cyl, pr.d, pr.o);
		if (texture.x < 100)
			t.t1 = INF;

		pr.o = o + (d * (t.t2));
		pr.d = pr.o - (cyl.center);
		pr.d = cross(pr.d, cyl.norm);
		pr.d = cross(cyl.norm, pr.d);
		pr.d = pr.d * (1.0f / length(pr.d));

		texture = gtexture(cyl, pr.d, pr.o);
		if (texture.x < 100)
			t.t2 = INF;
	}
	slicer(cyl, &t,	o, d);
	return (t);
}

t_roots	ft_intersect_ray_plane(float3 o, float3 d, t_object plane)
{
	float3	oc;
	float		k1;
	t_roots	t;

	t.t1 = INF;
	t.t2 = INF;
	oc = o - plane.center;
	k1 = dot(d, plane.norm);
	
		t.t1 = - dot(oc, plane.norm) / k1;
		t.t2 = - dot(oc, plane.norm) / k1;

	slicer(plane, &t,	o, d);
	
	return (t);
}

t_roots	ft_intersect_ray_sphere(float3 o, float3 d, t_object sphere)
{
	float3		oc;
	float3		k;
	float		disc;
	t_roots	t;
	t_ray		pr;
	float3		texture;
	int 		i;

	oc = o - sphere.center;
	k.x = dot(d, d);
	k.y = 2.0f * dot(oc, d);
	k.z = dot(oc, oc) - pow(sphere.radius, 2);
	disc = k.y * k.y - 4 * k.x * k.z;

	if (disc < 0)
	{
		t.t1 = INF;
		t.t2 = INF;
		return (t);
	}

	t.t1 = (-k.y + sqrt(disc)) / (2.0f * k.x);
	t.t2 = (-k.y - sqrt(disc)) / (2.0f * k.x);

	if (t.t1 < t.t2)
		disc = t.t1;
	else
		disc = t.t2;

	if (sphere.textype == 'o')
	{
		pr.o = o + (d * (t.t1));
		pr.d = pr.o - (sphere.center);
		pr.d = pr.d * (1.0f / length(pr.d));

		texture = gtexture(sphere, pr.d, pr.o);
		if (texture.x < 100)
			t.t1 = INF;

		pr.o = o + (d * (t.t2));
		pr.d = pr.o - (sphere.center);
		pr.d = pr.d * (1.0f / length(pr.d));

		texture = gtexture(sphere, pr.d, pr.o);
		if (texture.x < 100)
			t.t2 = INF;
		
	}

	if (sphere.textype == 'd')
		{
			pr.o = o + (d * (disc));
			pr.d = pr.o - (sphere.center);
			pr.d = pr.d * (1.0f / length(pr.d));

			texture = gtexture(sphere, pr.d, pr.o) / 255;
			texture.x = (1 - texture.x) / sphere.radius / 2;
			k.z = dot(oc, oc) - pow((sphere.radius -  texture.x), 2);

			disc = k.y * k.y - 4 * k.x * k.z;
			i = 0;

			// while (disc < 0)
			// {
			// 	i++;
			// 	k.z = dot(oc, oc) - pow((sphere.radius - texture.x * (1000.0f - (float)(i)) / 1000.0f), 2);
			// 	disc = k.y * k.y - 4 * k.x * k.z;
			// }
			// if (disc < 0)
			// {
			// 	t.t1 =  t.t1 - texture.x;
			// 	t.t2 =  t.t1 - texture.x;
			// }
			//else
			{
				t.t1 = (-k.y + sqrt(disc)) / (2.0f * k.x);
				t.t2 = (-k.y - sqrt(disc)) / (2.0f * k.x);
			}
			
		}

	slicer(sphere, &t,	o, d);

	return (t);
}