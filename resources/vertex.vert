#version 330 core

layout (location = 0) in vec3 pos_;
layout (location = 1) in vec3 normal_;
layout (location = 2) in vec2 uv_;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 uv;
out vec3 normal;
out vec3 fragPos;


void main()
{
	uv = uv_;
	normal = normal_;
	fragPos = vec3(model * vec4(pos_, 1));
	
	gl_Position = projection * view * model * vec4(pos_, 1);

}