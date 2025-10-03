#version 430 core

layout(local_size_x = 16, local_size_y = 16, local_size_z = 1) in; // needs to be in

// input
layout(std430, binding=0) buffer _cameraRays { vec4 rayDirections[]; };

// output
layout(binding = 0, rgba8) writeonly uniform image2D outputTexture;
uniform ivec2 imgDimension;

void main()
{
	ivec2 gid = ivec2(gl_GlobalInvocationID.xy);

	int arrayIndex = gid.y * imgDimension.x + gid.x;

	// transform from [-1,1] (vector) --> [0,1] (color)
	vec3 vector = (rayDirections[arrayIndex].xyz + vec3(1,1,1)) * 0.5f;

	imageStore(outputTexture, gid, vec4(vector, 1) ); // 1 -> fully opaque
}