#define SPHERE_RADIUS	25.0f
#define SQUARE_SIZE		1.0f

void kernel initialize_sphere(__global Particle *particles)
{
	int i = get_global_id(0);
	global float4 *position = particles[i].position;
	uint	subDivCount = cbrt((float)100000);
	float2	delta = (float2)(M_PI * 2 / subDivCount, M_PI / subDivCount);
	float	radiusDelta = SPHERE_RADIUS / subDivCount;

	uint	x = fmod(i, (float)subDivCount);
	uint	y = fmod((float)i / subDivCount, (float)subDivCount);
	uint	r = i / (subDivCount * subDivCount);

	float radius = radiusDelta * r;

	float2	offset = (r % 2 == 0)
		? delta / 2
		: (float2)(0);

	position[i].x = radius * sin(delta.x * y + offset.x) * sin(delta.y * x + offset.y);
	position[i].y = radius * cos(delta.x * y + offset.x);
	position[i].z = radius * sin(delta.x * y + offset.x) * cos(delta.y * x + offset.y);

}
