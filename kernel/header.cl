#define GRAV_RADIUS 0.25f
#define PARTICLES_COUNT 1024000
#define SQUARE_SIZE		1.0f
#define G 9.81f
#define ATTRACT (G * 0.01f * 0.12f)
#define GA M_PI * (3.0f - sqrt(5.0f))
#define Z_HELPER ( 1.0 - (1.0 / (float)PARTICLES_COUNT) )
typedef struct
{
	float3	position;
	float3	color;
	float3	velocity;
}			Particle;
