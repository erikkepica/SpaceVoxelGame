#pragma once

class Vertex
{
public:
	Vertex(float x, float y, float z, float u, float v)
		: x(x), y(y), z(z), u(u), v(v) {}
	float x, y, z;
	float u, v;
};