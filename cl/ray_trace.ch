#define INF 4000001.0f
#define SLICE_UP 1
#define SLICE_DOWN 2
#define SAME_SIDE 1
#define DIFF_SIDE 0

typedef struct	s_lim
{
	float	max;
	float	min;
}				t_lim;

typedef struct	s_ray
{
	float3		o;
	float3		d;
}				t_ray;

typedef struct	s_object
{
	char		type;
	float		dist;
	float3		center;
	float		radius;
	float3		norm;
	float		alpha; //cone

	int3		color;
	int			specular;
	float		reflective;
	float		transparency;
	int			texture;
	char		textype;
	float2		shift;
	float2		scale;

	float4		slice[4];
	int			slice_side[4];

	int negative;
}				t_object;

typedef struct	s_source
{
	float3		position;
	float		intensity;
	char		type;
}				t_source;

typedef struct	s_roots
{
	float	root1;
	float	root2;
}				t_roots;

typedef struct	s_matrix
{
	float		m[3][3];
}				t_matrix;


typedef struct	s_scene
{
	t_object	objects[20];
	t_source	sources[10];
	float3		startviewpoint;
	float3		viewpoint;
	t_matrix	rot_matrix;
	t_lim		cl_lim;
	t_lim		tr_lim;
	int			effect;
	int			effect_int;
	float3		cam_angles;
	int			width;
	int			height;
}				t_scene;
