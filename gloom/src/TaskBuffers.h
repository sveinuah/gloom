#pragma once

#include <vector>

namespace TaskOne {
	std::vector<float> positions
	{
		-0.5f,	-0.5f,	0.f,
		0.5f,	-0.5f,	0.f,
		-0.0f,	0.5f,	0.f
	};

	std::vector<float> colors
	{
		0.8f,	0.0f,	0.0f,	1.0f,
		0.0f,	0.8f,	0.0f,	1.0f,
		0.0f,	0.0f,	0.8f,	1.0f
	};

	std::vector<uint32_t> indices
	{
		0, 1, 2
	};
}

namespace TaskTwo {
	std::vector<float> vertices
	{
		0.6f,	-0.8f,	-1.2f,
		0.f,	0.4f,	0.f,
		-0.8f,	-0.2f,	1.2f
	};

	std::vector<uint32_t> indices
	{
		0, 1, 2
	};
}