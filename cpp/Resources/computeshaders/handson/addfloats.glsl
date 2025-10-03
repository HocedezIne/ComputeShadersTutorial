#version 430

// has to be named in
layout(local_size_x = 256, local_size_y = 1, local_size_z = 1) in;

// A + B = C
// A buffer -> operand
layout(set = 0, binding = 0) readonly buffer _ALayout
	{
		float A[]; // -> use this in main
	};
layout(set = 0, binding = 1) readonly buffer _BLayout { float B[]; };
layout(set = 0, binding = 2) writeonly buffer _CLayout { float C[]; };

void main()
{
	uint i = gl_GlobalInvocationID.x;
	C[i] = A[i] + B[i];
}