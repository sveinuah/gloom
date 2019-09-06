#pragma once

#include <vector>

namespace TaskOne {
	std::vector<float> vertices
	{
		-0.8f,	-0.8f,	0.f,
		-0.6f,	-0.8f,	0.f,
		-0.7f,	-0.6f,	0.f,

		0.6f,	-0.8f,	0.f,
		0.8f,	-0.8f,	0.f,
		0.7f,	-0.6f,	0.f,

		-0.1f,	-0.8f,	0.f,
		0.1f,	-0.8f,	0.f,
		0.f,	-0.6f,	0.f,

		-0.45f,	-0.3f,	0.f,
		-0.25f,	-0.3f,	0.f,
		-0.35f,	-0.1f,	0.f,

		0.25f,	-0.3f,	0.f,
		0.45f,	-0.3f,	0.f,
		0.35f,	-0.1f,	0.f,

		-0.1f,	0.2f,	0.f,
		0.1f,	0.2f,	0.f,
		0.f,	0.4f,	0.f
	};

	std::vector<uint32_t> indices
	{
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		9, 10, 11,
		12, 13, 14,
		15, 16, 17
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