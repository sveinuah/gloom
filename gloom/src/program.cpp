// Local headers
#include "program.hpp"
#include "gloom/gloom.hpp"
#include "gloom/shader.hpp"

// Made a header file to hold the diferent buffers used in the assignment
#include "TaskBuffers.h"

std::vector<float> fillVertexBuffer(const std::vector<float>& positions, const std::vector<float>& colors)
{
	assert(positions.size() / 3 == colors.size() / 4); //Assert if there are different amounts of vvertices

	const uint32_t num_elems = positions.size() / 3;
	
	std::vector<float> vertices;
	vertices.reserve(num_elems * (3 + 4));

	for (int i = 0; i < num_elems; i++)
	{
		vertices.push_back(positions[3 * i]);
		vertices.push_back(positions[3 * i + 1]);
		vertices.push_back(positions[3 * i + 2]);
		vertices.push_back(colors[4 * i]);
		vertices.push_back(colors[4 * i + 1]);
		vertices.push_back(colors[4 * i + 2]);
		vertices.push_back(colors[4 * i + 3]);
	}

	return vertices;
}

uint32_t CreateTriangleVAO(const std::vector<float>& positions, const std::vector<float>& colors, const std::vector<uint32_t>& indices)
{
	uint32_t va_id = 0;
	glCreateVertexArrays(1, &va_id);
	glBindVertexArray(va_id);

	auto vertices = fillVertexBuffer(positions, colors);

	// Create Vertex Buffer and bind to VAO
	uint32_t v_id = 0;
	glCreateBuffers(1, &v_id);
	glBindBuffer(GL_ARRAY_BUFFER, v_id);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	// Layout positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3,	GL_FLOAT, GL_FALSE,	7 * sizeof(float), 0);
	
	//Layout colors
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));

	// Create Index Buffer and bind to VAO
	uint32_t i_id = 0;
	glCreateBuffers(1, &i_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

	// unbind to avoid accidental binding of new buffers to this VAO.
	glBindVertexArray(0);
	return va_id;
}


void runProgram(GLFWwindow* window)
{
    // Enable depth (Z) buffer (accept "closest" fragment)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Configure miscellaneous OpenGL settings
    glEnable(GL_CULL_FACE);

	// Configure color blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set default colour after clearing the colour buffer
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

    // Set up your scene here (create Vertex Array Objects, etc.)

	uint32_t va_id = CreateTriangleVAO(TaskOne::positions, TaskOne::colors, TaskOne::indices);

	Gloom::Shader shader;
	shader.makeBasicShader(
		R"(C:\Users\Sveinung\Source\Repos\gloom\gloom\shaders\simple.vert)",
		R"(C:\Users\Sveinung\Source\Repos\gloom\gloom\shaders\simple.frag)"
	);

    // Rendering Loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear colour and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw your scene here
		shader.activate();
		
		glBindVertexArray(va_id);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		shader.deactivate();


        // Handle other events
        glfwPollEvents();
        handleKeyboardInput(window);

        // Flip buffers
        glfwSwapBuffers(window);
    }
}


void handleKeyboardInput(GLFWwindow* window)
{
    // Use escape key for terminating the GLFW window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
