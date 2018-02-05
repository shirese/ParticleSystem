void kernel initialize(__global Particle *particles, __global int *shape)
{
	int i = get_global_id(0);
	float3 dir;

	if (*shape == 1)
	{
		float ga = M_PI * (3.0 - sqrt(5.));
		float theta = ga * (float)i;
		float z = ( 1.0 - (1.0 / (float)PARTICLES_COUNT) ) * ( 1.0 - ( (2. * (float)i) / ( (float)PARTICLES_COUNT - 1.0 ) ) );
		float radius = sqrt(1.0	 - z * z);
		dir.x = radius * cos(theta);
		dir.y = radius * sin(theta);
		dir.z = z;
		dir = particles[i].position - dir;
		particles[i].velocity = (float3)0.4 * dir;
		particles[i].position = particles[i].velocity;
	}
	else if (*shape == 2)
	{
		uint	subDivCount = cbrt((float)PARTICLES_COUNT);
		uint	x = fmod((float)i, (float)subDivCount);
		uint	y = fmod((float)i / subDivCount, (float)subDivCount);
		uint	z = i / (subDivCount * subDivCount);
		float	subDivSize = SQUARE_SIZE / subDivCount;
		float	subDivSize2 = subDivSize / 2.0f;
		dir.x = x * subDivSize - 0.5 + subDivSize2;
		dir.y = y * subDivSize - 0.5 + subDivSize2;
		dir.z = z * subDivSize - 0.5 + subDivSize2;
		dir = particles[i].position - dir;
		particles[i].velocity = (float3)0.4 * dir;
		particles[i].position = particles[i].velocity;
	}
	particles[i].color.x = 1.;
	particles[i].color.y = 0.15;
	particles[i].color.z = 0.15;
	//float phi = ( sqrt(5.f) + 1.f ) / 2.f - 1.f; // golden ratio
	//float ga = phi * 2.f * M_PI;

	/*uint	subDivCount = cbrt((float)PARTICLES_COUNT);
	float2	delta = (float2)(M_PI * 2 / subDivCount, M_PI / subDivCount);
	float	radiusDelta = SPHERE_RADIUS / subDivCount;

	uint	x = fmod(i, (float)subDivCount);
	uint	y = fmod((float)i / subDivCount, (float)subDivCount);
	uint	r = i / (subDivCount * subDivCount);

	float radius = radiusDelta * r;

	float2	offset = (r % 2 == 0)
		? delta / 2
		: (float2)(0);

	particles[i].position.x = radius * sin(delta.x * y + offset.x) * sin(delta.y * x + offset.y);
	particles[i].position.y = radius * cos(delta.x * y + offset.x);
	particles[i].position.z = radius * sin(delta.x * y + offset.x) * cos(delta.y * x + offset.y);*/

	/*float lon = ga * i;
	lon /= 2.f * M_PI;
	lon -= floor(lon);
	lon *= 2.f * M_PI;
	if (lon > M_PI)
		lon -= 2.f * M_PI;
	// Convert dome height (which is proportional to surface area) to latitude
	float lat = asin(-1 + 2 * i / (float)PARTICLES_COUNT);
	particles[i].position.x = SPHERE_RADIUS * cos(lat) * cos(lon);
	particles[i].position.y = SPHERE_RADIUS * cos(lat) * sin(lon);
	particles[i].position.z = SPHERE_RADIUS * sin(lat);*/
	//printf("%f %f %f\n", particles[i].position.x, particles[i].position.y, particles[i].position.z);
}
