#pragma once
#include "Component.h"

#include <glm/glm.hpp>

class Transform : public Component
{
public:
	Transform()
	{
		position = { 0.0f, 0.0f, 0.0f };
		scale = { 1.0f, 1.0f, 1.0f };
		rotation = { 0.0f, 0.0f, 0.0f };
	}
	Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	{
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;
	}

	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
};