void kernel update_position(__global Particle *particles, __global float3 *gravityCenter)
{
	int					i = get_global_id(0);
	float				dist;
	float				minGravityDist;
	float				dx, dy, dz, force;

	minGravityDist = 0.75;
	dx = gravityCenter->x - particles[i].position.x;
	dy = gravityCenter->y - particles[i].position.y;
	dz = gravityCenter->z - particles[i].position.z;
	dist = sqrt(dx * dx + dy * dy + dz * dz);
	if (dist >= minGravityDist) {
		dx /= dist;
		dy /= dist;
		dz /= dist;
		force = G * ((1.f * 1.25) / (dist * dist));
		particles[i].velocity.x = dx * force / 1.;
		particles[i].velocity.y = dy * force / 1.;
		particles[i].velocity.z = dz * force / 1.;
		normalize(particles[i].velocity);
		particles[i].position += particles[i].velocity;
	}
}
