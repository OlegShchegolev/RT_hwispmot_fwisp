
float3		gtexture(t_object obj, float3 pr, float3 o)
{
	float2		uv;
	float3		texture;
	float2		shift;
	float2		scale;

	shift = (float2)(0.0f, 0.0f);
	scale = (float2)(3.0f, 5.0f);

	scale = obj.scale;
	shift = obj.shift;

	shift = (float2)(0.0f, 0.0f);

	uv.x = 0.5f + atan2(pr.z, pr.x) / (2.0f * M_PI_F);
	uv.y = 0.5f - asin(pr.y) / M_PI_F;

	if (obj.type == 'c')
	{
		pr = cross(obj.center - o, obj.norm);

		uv.x = 0.5f + atan2(pr.z, pr.x) / (2.0f * M_PI_F);
		if (obj.norm.z > obj.norm.y && obj.norm.z > obj.norm.x)
			uv.x = 0.5f + atan2(pr.x, pr.y) / (2.0f * M_PI_F);
		if (obj.norm.x > obj.norm.y && obj.norm.x > obj.norm.z)
			uv.x = 0.5f + atan2(pr.z, pr.y) / (2.0f * M_PI_F);
		// float3 oz = (float3)(0.0f, 0.0f, 1.0f);
		// if (obj.norm.z > obj.norm.y && obj.norm.z > obj.norm.x)
		// 	oz = (float3)(1.0f, 0.0f, 0.0f);
		// if (obj.norm.x > obj.norm.y && obj.norm.x > obj.norm.z)
		// 	oz = (float3)(0.0f, 1.0f, 0.0f);
		//	uv.x = 0.5f + atan2(length(cross(pr, oz)) , dot(pr, oz)) / (2.0f * M_PI_F);
		//	uv.x = 0.5f + atan2(length(cross(pr, oz)) , dot(pr, oz)) / (2.0f * M_PI_F);
		//	uv.x = 0.5f + atan2(o.z - obj.center.z, o.x - obj.center.x) / (2.0f * M_PI_F);
		//	uv.y = (- o.y + obj.center.y) / 10;
		uv.y = length(obj.center - o) * dot(obj.center - o, obj.norm) / length(obj.center - o) / length(obj.norm) / (10);
	}

	if (obj.type == 't')
	{
		pr = cross(obj.center - o, obj.norm);

		uv.x = 0.5f + atan2(pr.z, pr.x) / (2.0f * M_PI_F);
		if (obj.norm.z > obj.norm.y && obj.norm.z > obj.norm.x)
			uv.x = 0.5f + atan2(pr.x, pr.y) / (2.0f * M_PI_F);
		if (obj.norm.x > obj.norm.y && obj.norm.x > obj.norm.z)
			uv.x = 0.5f + atan2(pr.z, pr.y) / (2.0f * M_PI_F);

		uv.y = length(obj.center - o) * dot(obj.center - o, obj.norm) / length(obj.center - o) / length(obj.norm) / (10);
	}

	if (obj.type == 'p')
	{
		uv.x = ( o.x - obj.center.x) / 10;
		uv.y = (- o.y + obj.center.y) / 10;
		if (obj.norm.y > obj.norm.x && obj.norm.y > obj.norm.x)
		{
			uv.x = ( o.x - obj.center.x) / 10;
			uv.y = (- o.z + obj.center.z) / 10;
		}
		if (obj.norm.x > obj.norm.y && obj.norm.x > obj.norm.z)
		{
			uv.x = ( o.z - obj.center.z) / 10;
			uv.y = (- o.y + obj.center.y) / 10;
		}
	}

	uv.x = uv.x + shift.x;
	uv.y = uv.y + shift.y;

	uv.x = uv.x * scale.x;
	uv.y = uv.y * scale.y;


	if (uv.y < 0.0f)
	{
		uv.y = uv.y - ((int)(uv.y) - 1);	
	}
	if (uv.x < 0.0f)
	{
		uv.x = uv.x - ((int)(uv.x) - 1);	
	}
	
	if (uv.x > 1.0f)
		uv.x = uv.x - ((int)(uv.x));
	if (uv.y > 1.0f)
		uv.y = uv.y - ((int)(uv.y));
		


	texture.x = 255.0f;
	texture.y = 255.0f;
	texture.z = 255.0f;

	if (obj.texture == 1)
	{
		if (((int)(uv.x * 24) % 2 && ((int)(uv.y * 10) % 2)) || (!((int)(uv.x * 24) % 2) && !((int)(uv.y * 10) % 2)) )
			texture.x = 0.3f;
	}
	// if (obj.texture == 6)
	// {
	// 	texture.x = 20 * convert_float(map6[((int)(uv.x * 1022) * 512 + (int)(uv.y * 512))] - map6[(((int)(uv.x * 1022) + 1) * 512 + (int)(uv.y * 512))]);
	// 	texture.y = 20 * convert_float(map6[((int)(uv.x * 1022) * 512 + (int)(uv.y * 512))] - map6[((int)(uv.x * 1022) * 512 + 1 + (int)(uv.y * 512))]);
	// 	texture.z = convert_float(map6[((int)(uv.x * 1024) * 512 + (int)(uv.y * 512))]);
	// }
	// if (obj.texture == 2)
	// {
	// 	texture.x = map2[((int)(uv.x * 699) * 420 + (int)(uv.y * 420))].x;
	// 	texture.y = map2[((int)(uv.x * 699) * 420 + (int)(uv.y * 420))].y;
	// 	texture.z = map2[((int)(uv.x * 699) * 420 + (int)(uv.y * 420))].z;
	// }

	// if (obj.texture == 8)
	// {
	// 	texture.x = convert_float(map8[((int)(uv.x * 200) * 100 + (int)(uv.y * 100))]);
	// 	texture.y = convert_float(map8[((int)(uv.x * 200) * 100 + (int)(uv.y * 100))]);
	// 	texture.z = convert_float(map8[((int)(uv.x * 200) * 100 + (int)(uv.y * 100))]);
	// }
	// if (obj.texture == 7)
	// {
	// 	//texture.x = convert_float(map[((int)(uv.x * 1022) * 512 + (int)(uv.y * 512))]) / 100;
		
	// 	texture.x = uv.y * native_cos((uv.x) * 10 * M_PI_F) * native_cos((uv.y) * 10 * M_PI_F) * 255;
	// 	texture.y = uv.y * sin((uv.x) * 10 * M_PI_F) * sin((uv.y) * 10 * M_PI_F) * 255;
	// 	texture.z = uv.y * sin((uv.x) * 10 * M_PI_F) * sin((uv.y) * 10 * M_PI_F) * 255;
	// }

	// if (obj.texture == 9)
	// {
	// 	texture.x = convert_float(map9[((int)(uv.x * 1022) * 512 + (int)(uv.y * 512))]);
	// 	texture.y = convert_float(map9[((int)(uv.x * 1022) * 512 + (int)(uv.y * 512))]);
	// 	texture.z = convert_float(map9[((int)(uv.x * 1022) * 512 + (int)(uv.y * 512))]);

	// }
	// if (obj.texture == 3)
	// {
	// 	if (((int)(uv.y  * 30 * sin((uv.x) * M_PI_F)) % 2))
	// 		texture.x = 0.3f;
	// }
	return (texture);
}