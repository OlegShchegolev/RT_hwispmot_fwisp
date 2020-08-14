#include "cl/ray_trace.h"

t_ray		new_pr(t_ray od, t_object obj, float dist, int4 *txt, int2 txt_size)
{
	t_ray		pr;
	float3		texture;

	if (obj.type == 's')
	{
		pr.o = od.o + (od.d * dist);
		pr.d = pr.o - (obj.center);
		pr.d = pr.d * (1.0f / length(pr.d));
		if (obj.textype == 'b')
		{
			texture = gtexture(obj, pr.d, pr.o, txt, txt_size);
			od.d = normalize(od.d) + normalize(cross(od.d, (float3)(1.0f, 0.0f, 0.0f))) * (texture.x / 255) + normalize(cross(od.d, (float3)(0.0f, 1.0f, 0.0f))) * (texture.y / 255);
		}
	}
	if (obj.type == 'p')
	{
		pr.o = od.o + (od.d * dist);
		// pr.d = pr.o - obj.center;
		// pr.d = cross(pr.d, obj.norm);
		// pr.d = cross(obj.norm, pr.d);
		pr.d = obj.norm;
		pr.d = pr.d * (1.0f / length(pr.d));
	}
	if (obj.type == 'c')
	{
		pr.o = od.o + (od.d * dist);
		pr.d = pr.o - obj.center;
		pr.d = cross(pr.d, obj.norm);
		pr.d = cross(obj.norm, pr.d);
		pr.d = pr.d * (1.0f / length(pr.d));
	}
	if (obj.type == 't')
	{
		pr.o = od.o + (od.d * dist);
		pr.d = pr.o - obj.center;
		pr.d = cross((obj.norm * dot(obj.norm, pr.d)), pr.d);
		pr.d = cross(pr.d, (pr.o - obj.center));
		pr.d = pr.d * (1.0f / length(pr.d));
	}
	return (pr);
}

float3		apply_bump(t_ray od, t_object obj, float dist, int4 *txt, int2 txt_size)
{
	t_ray		pr;
	float3		texture;
	float3		norm;

	if (obj.type == 's')
	{
		pr.o = od.o + (od.d * dist);
		pr.d = pr.o - (obj.center);
		norm = pr.d * (1.0f / length(pr.d));
		
		if (obj.textype == 'b')
		{
			texture = gtexture(obj, norm, pr.o, txt, txt_size);
			od.d = normalize(od.d) + normalize(cross(od.d, (float3)(1.0f, 0.0f, 0.0f))) * (texture.x / 255) + normalize(cross(od.d, (float3)(0.0f, 1.0f, 0.0f))) * (texture.y / 255);
		}
	}
	return(od.d);
}

float3		obj_col(t_ray pr, t_object obj, int4 *txt, int2 txt_size)
{
	float3		back;

	back = convert_float3(obj.color);
	if (obj.texture > 0)
		back = gtexture(obj, pr.d, pr.o, txt, txt_size);
	return (back);
}