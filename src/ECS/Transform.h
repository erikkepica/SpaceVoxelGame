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

	glm::vec3 Transform::Forward() const
	{
		float yaw = glm::radians(rotation.y-90);
		float pitch = glm::radians(rotation.x);

		return glm::normalize(glm::vec3(
			cos(yaw) * cos(pitch),  // swapped: was sin(yaw)
			-sin(pitch),
			sin(yaw) * cos(pitch)   // swapped: was cos(yaw)
		));
	}

	glm::vec3 Transform::Right() const
	{
		float yaw = glm::radians(rotation.y-90);

		return glm::normalize(glm::vec3(
			-sin(yaw),  // swapped: was cos(yaw)
			0.0f,
			cos(yaw)    // swapped: was -sin(yaw)
		));
	}
};