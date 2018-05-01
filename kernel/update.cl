// float3 getParticleColor(float dist, float3 particlePosition)
// {
// 	float3 color;

// 	dist *= 0.25f;
// 	color.x = 1 - dist;
// 	color.y = 0.0;
// 	color.z = dist;
// 	return (color);
// }

void kernel update_position(__global Particle *particles, __constant float3 *gravityCenter)
{
	int					i = get_global_id(0);
	float				dist;
	float				force;
	float3				dir;
	float3				gtest;

	particles += i;
	gtest = float3(2, 2, -1);
	dir = gtest - particles->position;
	dist = distance(gtest, particles->position);
	if (dist < 0.001)
		dir *= (float3)0.001;
	if (dist < 0.01)
		dir *= (float3)0.05;
	if (dist < 0.03)
		dir *= (float3)0.01;
	if (dist < 1.0)
		dir *= (float3)0.1;
	if (dist < 10.0)
		dir *= (float3)0.1;
	if (dist > 0)
		particles->position += dir;
	else
		particles->position -= dir;
	// if (dist <= GRAV_RADIUS)
		// return ;
	// force = ATTRACT / (dist * dist);
	// particles->velocity += (*gravityCenter - particles->position) * force;
	// particles->position += particles->velocity;
	// dist *= 0.42f;
	// particles->color.x = 1 - dist;
	// particles->color.y = 1 - dist;
	// particles->color.z = dist;
	// getParticleColor(dist, particles->position);
	// particles->velocity *= 0.8f;
}
