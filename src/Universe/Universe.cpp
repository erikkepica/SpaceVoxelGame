#include"Universe/Universe.h"
#include <glm/gtc/matrix_transform.hpp>

#include"ECS/Entity.h"

#include"ECS/Transform.h"
#include"ECS/Renderer.h"

#include"Systems/RenderSystem.h"


Universe::Universe(std::shared_ptr<Window> window)
{
	this->window = window;

	m_RenderSystems.push_back(std::make_unique<RenderSystem>(this));

	Start();
}


void Universe::Start()
{
	m_Entity = std::make_shared<Entity>("TestEntity");

	m_Entity->AddComponent(std::make_shared<Transform>(), "default");
	m_Entity->transform = m_Entity->GetComponent<Transform>();


	m_Entity->AddComponent(std::make_shared<Renderer>());

	VertexBufferLayout vbl;
	vbl.Push<float>(3);
	vbl.Push<float>(2);

	m_Entity->GetComponent<Renderer>()->CreateMesh(vbl);

	//m_Entity.GetComponent<Renderer>()->shader.Generate(RESOURCES_PATH "raymarching.vert", RESOURCES_PATH "raymarching.frag");
	m_Entity->GetComponent<Renderer>()->shader.Generate(RESOURCES_PATH "vertex.vert", RESOURCES_PATH "fragment.frag");

	m_Entity->GetComponent<Renderer>()->texture.Generate(RESOURCES_PATH "penguin.png");



	m_Chunk = std::make_shared<Chunk>(16, 16);
	m_Chunk->GenerateChunk();
	m_Chunk->GenerateChunkMesh();
}



void Universe::Render()
{
	m_Projection = glm::perspective(glm::radians(45.0f),(float)window->data.width/ (float)window->data.height, 0.1f, 100.0f);

	for(auto& system : m_RenderSystems)
	{
		system->Tick(std::vector<std::shared_ptr<Entity>>{m_Entity, m_Chunk});
	}
}

void Universe::Update(float deltaTime)
{
	for (auto& system : m_UpdateSystems)
	{
		system->Tick(std::vector<std::shared_ptr<Entity>>{m_Entity});
	}
}
