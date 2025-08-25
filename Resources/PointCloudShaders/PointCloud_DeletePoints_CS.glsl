@WorldMatrix@

uniform vec3 Center;
uniform float Radius;

layout (local_size_x = 1024, local_size_y = 1, local_size_z = 1) in;

struct PointData
{
    vec3 position;
    uint color;
};

layout (std430, binding = 1) buffer ParticleBuffer
{
    PointData particles[];
};

layout(std430, binding = 2) buffer DeletionBuffer
{
	uint bDeletionOccurred;
};

void main()
{
	vec3 WorldPosition = particles[gl_GlobalInvocationID.x].position;
	WorldPosition = (FEWorldMatrix * vec4(WorldPosition, 1.0)).xyz;
	
	if (distance(Center, WorldPosition) < Radius)
	{
		if (bDeletionOccurred == 0)
		{
			// Check maybe that point is already marked as deleted.
			if ((particles[gl_GlobalInvocationID.x].color >> 24) != 0)
				atomicAdd(bDeletionOccurred, 1);
		}
		
		// Mark point as deleted by setting alpha to 0.
		particles[gl_GlobalInvocationID.x].color = (particles[gl_GlobalInvocationID.x].color & 0x00FFFFFF) | (0 << 24);
	}
}