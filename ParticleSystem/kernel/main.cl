#define SPHERE_RADIUS	1.5f

void kernel initialize_sphere(__global Particle *particles)
{
	int i = get_global_id(0);
	//float phi = ( sqrt(5.f) + 1.f ) / 2.f - 1.f; // golden ratio
	//float ga = phi * 2.f * M_PI;
	float ga = M_PI * (3. - sqrt(5.));
	float theta = ga * (float)i;
	float z = ( 1. - (1. / (float)PARTICLES_COUNT) ) * ( 1. - ( (2. * (float)i) / ( (float)PARTICLES_COUNT - 1. ) ) );
	float radius = sqrt(1. - z * z);
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

	particles[i].position.x = radius * cos(theta);
	particles[i].position.y = radius * sin(theta);
	particles[i].position.z = z;
	//printf("%f %f %f\n", particles[i].position.x, particles[i].position.y, particles[i].position.z);
}
