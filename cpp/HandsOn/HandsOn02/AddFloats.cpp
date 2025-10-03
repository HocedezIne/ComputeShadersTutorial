#include "AddFloats.h"
#include <iostream>

AddFloats::AddFloats(GLuint width, GLuint height) :
	m_AddFloatsComputeShader{ std::string("computeshaders/handson/addfloats.glsl") },
	m_Operand1Data{ 1024 },
	m_Operand2Data{ 1024 },
	m_Result{ 1024 }
{
}

AddFloats::~AddFloats()
{
}

void AddFloats::init(const SurfaceRenderer& renderer)
{
	// initialize compute shaders and buffers
	m_AddFloatsComputeShader.compile();
	m_Operand1Data.randomize(1, 100);
	m_Operand2Data.randomize(1, 100);

	m_Operand1Data.init();
	m_Operand2Data.init();

	m_Result.init();
}

void AddFloats::compute(const SurfaceRenderer& renderer)
{
	// use compute shader
	m_AddFloatsComputeShader.use();
	
	// bind buffers
	m_Operand1Data.bindAsCompute(0); // bind in slot 0
	m_Operand2Data.bindAsCompute(1);
	m_Result.bindAsCompute(2);

	// dispatch compute shader
	m_AddFloatsComputeShader.compute(m_Result.size(), 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);


	// download result. --> typically you want to download as little as possible
	m_Result.download(); // to avoid
	for (auto result : m_Result.getData())
	{
		std::cout << "Result: " << result << "\n";
	}
}
