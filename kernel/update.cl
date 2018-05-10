// float3 getParticleColor(float dist, float3 particlePosition)
// {
// 	float3 color;

// 	dist *= 0.25f;
// 	color.x = 1 - dist;
// 	color.y = 0.0;
// 	color.z = dist;
// 	return (color);
// }

void kernel update_position(__global Particle *particles, __constant float2 *gravityCenter)
{
	int					i = get_global_id(0);
	float				dist;
	float				force;
	float3				gc;
	float3				base_velocity;
	float3				dir;
	float3				gtest;

	particles += i;
	base_velocity = float3(0.01, 0.01, 0.01);
	gc = (float3)(*gravityCenter, 0.0);
	dir = (gc - particles->position);
	printf("%f %f %f\n", particles->position.x,  particles->position.y,  particles->position.z);
	dist = distance(gc, particles->position);
	if (dist <= GRAV_RADIUS)
		return ;
	force = 0.5 / (dist * dist);
	particles->position += base_velocity;
	particles->position += dir * force;
	// particles->position += -dir * force;
	// dist *= 0.42f;
	// particles->color.x = 1 - dist;
	// particles->color.y = 1 - dist;
	// particles->color.z = dist;
	// getParticleColor(dist, particles->position);
	// particles->velocity *= 0.8f;
}
