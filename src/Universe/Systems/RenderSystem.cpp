#include "RenderSystem.h"

#include"Universe/Universe.h"
#include"ECS/Entity.h"

#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	renderer->EBO.Bind();
	renderer->VAO.Bind();

	renderer->shader.Use();

	renderer->shader.SetMat4("model", model);
	renderer->shader.SetMat4("view", view);
	renderer->shader.SetMat4("projection", universe->GetProjection());


	renderer->texture.Bind();

	glDrawElements(GL_TRIANGLES, renderer->EBO.GetIndicesNum(), GL_UNSIGNED_INT, 0);

	VAO::Unbind();
	EBO::UnBind();
}
