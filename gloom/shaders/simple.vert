#version 430 core

in vec3 position;

void main()
{
	vec3 newpos = position * vec3(-1, -1, 1);
    gl_Position = vec4(newpos, 1.0f);
}
