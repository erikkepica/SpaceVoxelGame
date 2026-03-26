#include "RenderSystem.h"

#include"Universe/Universe.h"
#include"ECS/Entity.h"

#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include"ECS/Camera.h"
#include"ECS/Sun.h"

void RenderSystem::Tick(const std::vector<std::shared_ptr<Entity>>& entities)
{
	for(std::shared_ptr<Entity> entity : entities)
	{
		std::shared_ptr<Renderer> renderer = entity->GetComponent<Renderer>();
		if (renderer)
		{
			std::shared_ptr<Transform> transform = entity->transform;
			if (transform)
			{
				Render(renderer, transform);
			}
			else
			{
				Render(renderer);
			}
		}
	}
}

void RenderSystem::Render(std::shared_ptr<Renderer> renderer)
{
}

void RenderSystem::Render(std::shared_ptr<Renderer> renderer, std::shared_ptr<Transform> transform)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, transform->position);

	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));

	renderer->EBO.Bind();
	renderer->VAO.Bind();

	renderer->shader.Use();

	renderer->shader.SetVec3("sunPos", universe->mainCamera->transform->position);

	renderer->shader.SetVec3("sunPos", universe->mainSun->GetComponent<Sun>()->sunPos);
	renderer->shader.SetVec3("lightColor", glm::vec3(1,1,1));

	renderer->shader.SetMat4("model", model);
	renderer->shader.SetMat4("view", universe->mainCamera->GetComponent<Camera>()->GetViewMatrix(universe->mainCamera->transform));
	renderer->shader.SetMat4("projection", universe->mainCamera->GetComponent<Camera>()->projection);

	renderer->shader.SetMat3("normalMatrix", normalMatrix);

	renderer->BindTextures();

	renderer->shader.SetInt("diffuseTex", 0);
	renderer->shader.SetInt("specularTex", 1);

	glDrawElements(GL_TRIANGLES, renderer->EBO.GetIndicesNum(), GL_UNSIGNED_INT, 0);

	VAO::Unbind();
	EBO::UnBind();
}
