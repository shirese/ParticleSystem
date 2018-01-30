void kernel update_position(__global Particle *particles, __global float3 *gravityCenter)
{
	int					i = get_global_id(0);
	float3				dist;
	float				speed;
	float				invDist;
	float				minGravityDist;
	float				dx, dy, dz, force;

	dist[0] = gravityCenter->x - particles[i].position.x;
	dist[1] = gravityCenter->y - particles[i].position.y;
	dist[2] = gravityCenter->z - particles[i].position.z;
	invDist = 1.0f / dot(dist, dist);
	dist *= (200.0f * invDist);
	printf("[%f %f %f]\n", particles[i].velocity.x, particles[i].velocity.y, particles[i].velocity.z);
	particles[i].velocity += -particles[i].position * 0.005f - dist * 0.8f;
	printf("[%f %f %f]\n", particles[i].velocity.x, particles[i].velocity.y, particles[i].velocity.z);
	speed = dot(particles[i].velocity, particles[i].velocity);
	if (speed < 0.2f)
		particles[i].position = *gravityCenter + dist * (1 + 0.8f);
	particles[i].position += particles[i].velocity;
	particles[i].velocity *= 0.95f;
}
