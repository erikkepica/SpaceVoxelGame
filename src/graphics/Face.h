#pragma once
#include<array>

#include"Vertex.h"

#include<glm/glm.hpp>

class Face
{
public:
	Face(std::array<Vertex, 4> vertices, std::array<unsigned int, 6> indices, glm::vec3 normal, glm::vec3 cullNormal)
		: vertices(vertices), indices(indices), cullNormal(cullNormal), normal(normal)
	{
	}

	std::array<Vertex, 4> vertices;
	std::array<unsigned int, 6> indices;

	glm::vec3 cullNormal;
	glm::vec3 normal;
};