
float		compute_lighting(t_ray pn, float3 md, t_scene scene, int specular, int closest)
{
	float		intensity;
	t_source	s;
	t_ray		pl;
	t_ray		tmp;
	float		dist;
	float		tmpdist;
	int			i = -1;
	float		plane_vp;
	float		d;
	int obj;

	intensity = 0.0f;
	pl.o = pn.o;
	if (scene.objects[closest].type == 'p')
	{
		d = -1. * dot(scene.objects[closest].norm, scene.objects[closest].center);
		plane_vp = dot(scene.objects[closest].norm, scene.viewpoint) + d;
	}
	while (++i < 10)
		if (scene.sources[i].type == 'p')
		{
			s = scene.sources[i];
			if (scene.objects[closest].type == 'p')
				if ((dot(scene.objects[closest].norm, s.position) + d) * plane_vp < 0.)
					s.intensity = 0;
			pl.d = s.position - pn.o;

			obj = get_closest(pl, scene.objects, &dist, scene.cl_lim);
			if (scene.objects[obj].negative == 1)
			{
				tmp.o = pl.o + (pl.d)  * dist * 1.0001f ;
				tmp.d = (pl.d - pl.o ) / length(pl.d- pl.o) ;
				tmpdist = dist;
				obj = get_closest(tmp, scene.objects, &dist, scene.cl_lim);
				dist += tmpdist;
			}
			if (obj == -1)
			{
		 		if (dot(pn.d, pl.d) > 0.0f)
					intensity += s.intensity * dot(pn.d, pl.d) / length(pl.d);
				if (dot(pn.d, pl.d) < 0.0f && scene.objects[closest].type == 'p')
					intensity -= s.intensity * dot(pn.d, pl.d) / length(pl.d);
				if (specular <= 0)
					s.intensity = 0;
				pl.d = pn.d * (2.0f * dot(pn.d, pl.d)) - pl.d;
				if (dot(pl.d, md) > 0.0f)
					intensity += s.intensity * pow(dot(pl.d, md) / length(pl.d) / length(md), specular);
			}
		}
	return (1.f);
}