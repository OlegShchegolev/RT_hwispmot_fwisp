
t_roots	intersect_slice(t_object obj, float3 start, float3 direction, int i, t_roots *sqr_eq)
{
	t_roots	slice_res;
	float3 slice_vec;

	slice_vec.x = obj.slice[i].x;
	slice_vec.y = obj.slice[i].y;
	slice_vec.z = obj.slice[i].z;


	if (obj.slice[i].x * direction.x + obj.slice[i].y * direction.y + obj.slice[i].z * direction.z == 0)
	{
		slice_res.t1 = INF;
		slice_res.t2 = INF;
		return (slice_res);
	}
	else
	{
		slice_res.t1 = -(obj.slice[i].x * start.x + obj.slice[i].y * start.y
		+ obj.slice[i].z * start.z + obj.slice[i].w) / (obj.slice[i].x * direction.x
		+ obj.slice[i].y * direction.y + obj.slice[i].z * direction.z);
		slice_res.t2 = slice_res.t1;
		if (dot(slice_vec, direction) <= 0)
			slice_res.t2 = -10;
		else
			slice_res.t2 = 10;
	}
	return (slice_res);
}

void		slicer(t_object obj, t_roots *sqr_eq,	float3 start, float3 direction)
{
	int					i;
	t_roots				slice_res;

	i = -1;
	while (obj.slice_side[++i])
	{
		slice_res = intersect_slice(obj, start, direction, i, sqr_eq);
		if (slice_res.t1 == INF)
			return ;
		else
		{
			if (slice_res.t2  > 0)
			{
				if (sqr_eq->t1 <= slice_res.t1 && obj.slice_side[i] == SLICE_DOWN)
					sqr_eq->t1 = INF;
				if (sqr_eq->t2 <= slice_res.t1 && obj.slice_side[i] == SLICE_DOWN)
					sqr_eq->t2 = INF;
				if (sqr_eq->t1 >= slice_res.t1 && obj.slice_side[i] == SLICE_UP)
					sqr_eq->t1 = INF;
				if (sqr_eq->t2 >= slice_res.t1 && obj.slice_side[i] == SLICE_UP)
					sqr_eq->t2 = INF;
   			}
			else
			{
				if (sqr_eq->t1 <= slice_res.t1 && obj.slice_side[i] == SLICE_UP)
					sqr_eq->t1 = INF;
				if (sqr_eq->t2 <= slice_res.t1 && obj.slice_side[i] == SLICE_UP)
					sqr_eq->t2 = INF;
				if (sqr_eq->t1 >= slice_res.t1 && obj.slice_side[i] == SLICE_DOWN)
					sqr_eq->t1 = INF;
				if (sqr_eq->t2 >= slice_res.t1 && obj.slice_side[i] == SLICE_DOWN)
					sqr_eq->t2 = INF;
			}
		}
	}
}