#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

layout(location = 2) uniform mat4 mvp = mat4(1.0);

out vec4 v_Color;

void main()
{
	v_Color = color;
    gl_Position = mvp * vec4(position, 1.0f);
}
