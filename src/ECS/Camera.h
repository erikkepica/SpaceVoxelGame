#pragma once
#include"Component.h"
#include"Transform.h"

#include"glm/gtc/matrix_transform.hpp"
#include<memory>

#include<GLFW/glfw3.h>
class Camera : public Component
{
public:
	float nearPlane = .1f;

	float FOV = 90.0f;

	glm::mat4 projection;

	Camera()
	{
	}

	glm::mat4 GetViewMatrix(std::shared_ptr<Transform> transform)
	{
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::rotate(view, glm::radians(transform->rotation.x), glm::vec3(1, 0, 0));
		view = glm::rotate(view, glm::radians(transform->rotation.y), glm::vec3(0, 1, 0));
		view = glm::rotate(view, glm::radians(transform->rotation.z), glm::vec3(0, 0, 1));
		view = glm::translate(view, -transform->position);
		return view;
	}

	void SetProjection(float aspectRatio)
	{
		projection = glm::infinitePerspective(glm::radians(FOV), aspectRatio, nearPlane);
	}
};