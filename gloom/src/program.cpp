// Local headers
#include "program.hpp"
#include "gloom/gloom.hpp"
#include "gloom/shader.hpp"
#include "Buffer.h"


void runProgram(GLFWwindow* window)
{
    // Enable depth (Z) buffer (accept "closest" fragment)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Configure miscellaneous OpenGL settings
    glEnable(GL_CULL_FACE);

    // Set default colour after clearing the colour buffer
    glClearColor(0.3f, 0.5f, 0.8f, 1.0f);

    // Set up your scene here (create Vertex Array Objects, etc.)

	uint32_t va_id = 0;
	glCreateVertexArrays(1, &va_id);
	glBindVertexArray(va_id);

	float vertices[3 * 3]
	{
		-0.6,	-0.6,	0,
		0.6,	-0.6,	0,
		0,		0.6,	0
	};

	BufferLayout layout
	{
		{"position", DataType::Float3}
	};
	VertexBuffer vertexbuffer{ vertices, sizeof(vertices), layout };

	vertexbuffer.Bind();
	uint32_t index = 0;
	for (const auto& element : layout)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(
			index,
			element.GetElementCount(),
			ToGLType(element.type),
			element.normalized ? GL_TRUE : GL_FALSE,
			layout.GetStride(),
			(const void*)element.offset
		);
		index++;
	}

	uint32_t indicies[3]{ 0, 1, 2 };
	IndexBuffer indexbuffer{ indicies, sizeof(indicies) / sizeof(uint32_t) };
	indexbuffer.Bind();

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
		vertexbuffer.Bind();
		indexbuffer.Bind();
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
