#pragma once
#include"Application/Window.h"
#include"Systems/System.h"

#include<glm/glm.hpp>
#include<vector>

#include"Data/Registries/BlockRegistry.h"

struct StarType
{
	glm::vec3 color;
	float temperature; // Kelvin
};

// Spectral classes: O B A F G K M
static const StarType STAR_TYPES[] =
{
	{ glm::vec3(0.60f, 0.70f, 1.00f), 35000.0f }, // O - blue 0
	{ glm::vec3(0.70f, 0.80f, 1.00f), 20000.0f }, // B - blue white 1
	{ glm::vec3(0.83f, 0.87f, 1.00f),  9000.0f }, // A - white 2
	{ glm::vec3(1.00f, 1.00f, 0.90f),  7000.0f }, // F - yellow white 3
	{ glm::vec3(1.00f, 0.95f, 0.80f),  5800.0f }, // G - yellow (sun-like) 4
	{ glm::vec3(1.00f, 0.75f, 0.50f),  4500.0f }, // K - orange 5
	{ glm::vec3(1.00f, 0.60f, 0.35f),  3200.0f }  // M - red 6
}; 

class Entity;
class Body;

class Universe
{
public:
	Universe(std::shared_ptr<Window> window);

	void RegisterBlockData();

	void Start();

	void Render();
	
	void Update(float deltaTime);

	std::shared_ptr<Window> window;

	std::shared_ptr<Entity> mainCamera;

	std::shared_ptr<Entity> mainSun;


	std::unique_ptr<BlockRegistry> blockRegistry;
private:

	std::shared_ptr<Entity> m_Camera;
	std::shared_ptr<Body> m_Asteroid;
	std::shared_ptr<Entity> m_Sun;
	
	std::vector<std::unique_ptr<System>> m_RenderSystems;
	std::vector<std::unique_ptr<System>> m_UpdateSystems;

};