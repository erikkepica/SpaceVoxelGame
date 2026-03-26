#include "SunSystem.h"
#include"ECS/Renderer.h"
#include"ECS/Sun.h"
#include"ECS/Camera.h"

#include"ECS/Entity.h"

#include"Universe/Universe.h"

void SunSystem::Tick(const std::vector<std::shared_ptr<Entity>>& entities)
{
	for(int i = 0; i < entities.size(); i++)
	{
		std::shared_ptr<Renderer> renderer = entities[i]->GetComponent<Renderer>();
		std::shared_ptr<Sun> sun = entities[i]->GetComponent<Sun>();
		
		if(renderer && sun)
		{
			Render(renderer, sun);
		}
	}
}

void SunSystem::Render(std::shared_ptr<Renderer> renderer, std::shared_ptr<Sun> sun)
{
	renderer->EBO.Bind();
	renderer->VAO.Bind();
	
	renderer->shader.Use();

	glm::mat4 invViewProj = glm::inverse(universe->mainCamera->GetComponent<Camera>()->projection * universe->mainCamera->GetComponent<Camera>()->GetViewMatrix(universe->mainCamera->GetComponent<Transform>()));

	renderer->shader.SetMat4("invViewProj", invViewProj);
	renderer->shader.SetVec3("camPos", universe->mainCamera->transform->position);

	renderer->shader.SetVec2("resolution", universe->window->data.width, universe->window->data.height);
	
	renderer->shader.SetFloat("sunIntensity", sun->sunIntensity);
	renderer->shader.SetFloat("sunTemperature", sun->sunTemperature);

	renderer->shader.SetFloat("sunRadius", sun->sunRadius);
	renderer->shader.SetVec3("sunPos", sun->sunPos);
	
	glDrawElements(GL_TRIANGLES, renderer->EBO.GetIndicesNum(), GL_UNSIGNED_INT, 0);
	
	VAO::Unbind();
	EBO::UnBind();
}