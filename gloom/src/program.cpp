// Local headers
#include "program.hpp"
#include <glm/glm.hpp>
#include "gloom/gloom.hpp"
#include "gloom/shader.hpp"
#include <chrono>

// Made a header file to hold the diferent buffers used in the assignment
#include "TaskBuffers.h"

std::vector<float> fillVertexBuffer(const std::vector<float>& positions, const std::vector<float>& colors)
{
	assert(positions.size() / 3 == colors.size() / 4); //Assert if there are different amounts of vertices

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

	uint32_t va_id = CreateTriangleVAO(TaskThree::positions, TaskThree::colors, TaskThree::indices);

	Gloom::Shader shader;
	shader.makeBasicShader(
		R"(..\..\..\gloom\shaders\simple.vert)",
		R"(..\..\..\gloom\shaders\simple.frag)"
	);

	// Uniform for ModelViewProjection matrix
	glm::mat4x4 scale{1.0f};
	glm::mat4x4 rotation{1.0f};
	glm::mat4x4 translation{1.0f};

	const float pi = 3.141592f;
	float scale_angle = 0.0f;
	float rotation_angle = 0.0f;
	float translation_angle = 0.0f;

	const float scale_speed = 1.3f;
	const float rotation_speed = 0.7f;
	const float translation_speed = 2.1f;

	using namespace std::chrono;
	using namespace std::chrono_literals;
	using Seconds = std::chrono::duration<float, std::ratio<1>>;

	auto last = steady_clock::now();
	auto curr = last;

    // Rendering Loop
    while (!glfwWindowShouldClose(window))
    {
		curr = steady_clock::now();
		nanoseconds dt = (curr - last);
		last = curr;

        // Clear colour and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Scaling

		scale_angle += scale_speed * Seconds(dt).count();
		scale[0][0] = 1 + 0.5 * std::sin(scale_angle);
		scale[1][1] = 1 + 0.5 * std::sin(scale_angle);
		scale[2][2] = 1 + 0.5 * std::sin(scale_angle);

		// Angle calculations
		rotation_angle += rotation_speed * Seconds(dt).count();
		rotation[0][0] = std::cos(rotation_angle);
		rotation[1][1] = std::cos(rotation_angle);
		rotation[0][1] = -std::sin(rotation_angle);
		rotation[1][0] = std::sin(rotation_angle);

		// Translations

		translation_angle += translation_speed * Seconds(dt).count();
		translation[0][3] = std::sin(translation_angle);
		translation[1][3] = std::cos(translation_angle);


        // Draw your scene here
		shader.activate();
		
		glBindVertexArray(va_id);
		auto mvp = scale * rotation * translation;
		glUniformMatrix4fv(2, 1, GL_TRUE, (float*)&mvp);
		glDrawElements(GL_TRIANGLES, 3 * 3, GL_UNSIGNED_INT, 0);

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
