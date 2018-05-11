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
	float				r;
	float				force;
	float				orbital_speed;
	float3				gc;
	float3				dir;
	float3				gtest;

	particles += i;
	gc = (float3)(*gravityCenter, 0.0);
	r = fast_distance(gc, particles->position);
	if (r <= GRAV_RADIUS)
		return ;
		// particles->velocity += (float3)0.01f;
	dir = (gc - particles->position);
	fast_normalize(dir);
	force = ATTRACT / (r * r);
	if (force > 10.0f)
		particles->velocity *= (float3)0.0001f * force;
	// if (!particles->velocity.x)
	// 	particles->velocity = float3(0.0001f, 0.0001f, 0);
	// else
	// {
	// 	orbital_speed = sqrt((0.24f * G) / r);
	// 	particles->velocity *= (float3)orbital_speed;
	// }
	particles->velocity += dir * force;
	particles->position += particles->velocity;
	// particles->velocity *= (float3)0.4;
	// particles->position += -dir * force;
	// dist *= 0.42f;
	// particles->color.x = gravityCenter->x;
	// particles->color.y = 10 * particles->velocity.y;
	// particles->color.z = gravityCenter->y;
	// getParticleColor(dist, particles->position);
	// particles->velocity *= 0.8f;
}
