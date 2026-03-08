#version 330 core

layout (location = 0) in vec3 pos_;
layout (location = 1) in vec2 uv_;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 uv;


void main()
{
	uv = uv_;
	
	gl_Position = vec4(pos_, 1);

}