#pragma once
#include"Application/Window.h"
#include"Systems/System.h"

#include<glm/glm.hpp>
#include<vector>

#include"Data/Registries/BlockRegistry.h"


class Entity;
class Chunk;

class Universe
{
public:
	Universe(std::shared_ptr<Window> window);

	void RegisterBlockData();

	void Start();

	void Render();
	
	void Update(float deltaTime);

	glm::mat4 GetProjection() { return m_Projection; }

	std::shared_ptr<Window> window;

	std::shared_ptr<Entity> mainCamera;

	std::unique_ptr<BlockRegistry> blockRegistry;
private:

	std::shared_ptr<Entity> m_Camera;
	std::shared_ptr<Chunk> m_Chunk;
	
	std::vector<std::unique_ptr<System>> m_RenderSystems;
	std::vector<std::unique_ptr<System>> m_UpdateSystems;

	glm::mat4 m_Projection;
};