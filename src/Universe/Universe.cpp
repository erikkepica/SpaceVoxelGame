#include"Universe/Universe.h"
#include <glm/gtc/matrix_transform.hpp>

#include"ECS/Entity.h"

#include"ECS/Transform.h"
#include"ECS/Renderer.h"
#include"ECS/Camera.h"

#include"Systems/RenderSystem.h"

#include"ECS/Chunk.h"

Universe::Universe(std::shared_ptr<Window> window)
{
	this->window = window;

	m_RenderSystems.push_back(std::make_unique<RenderSystem>(this));

    RegisterBlockData();
	Start();
}

void Universe::RegisterBlockData()
{
    std::vector<Face> faces;
    // Front (z = +0.5)
    faces.push_back(Face(
        std::array<Vertex, 4>{
        Vertex(-0.5, -0.5, 0.5, 0, 0),
            Vertex(0.5, -0.5, 0.5, 1, 0),
            Vertex(0.5, 0.5, 0.5, 1, 1),
            Vertex(-0.5, 0.5, 0.5, 0, 1)
    },
        std::array<unsigned int, 6>{0, 1, 2, 0, 2, 3},
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1)
    ));
    // Back (z = -0.5)
    faces.push_back(Face(
        std::array<Vertex, 4>{
        Vertex(0.5, -0.5, -0.5, 0, 0),
            Vertex(-0.5, -0.5, -0.5, 1, 0),
            Vertex(-0.5, 0.5, -0.5, 1, 1),
            Vertex(0.5, 0.5, -0.5, 0, 1)
    },
        std::array<unsigned int, 6>{0, 1, 2, 0, 2, 3},
        glm::vec3(0, 0, -1),
        glm::vec3(0, 0, -1)
    ));
    // Left (x = -0.5)
    faces.push_back(Face(
        std::array<Vertex, 4>{
        Vertex(-0.5, -0.5, -0.5, 0, 0),
            Vertex(-0.5, -0.5, 0.5, 1, 0),
            Vertex(-0.5, 0.5, 0.5, 1, 1),
            Vertex(-0.5, 0.5, -0.5, 0, 1)
    },
        std::array<unsigned int, 6>{0, 1, 2, 0, 2, 3},
        glm::vec3(-1, 0, 0),
        glm::vec3(-1, 0, 0)
    ));
    // Right (x = +0.5)
    faces.push_back(Face(
        std::array<Vertex, 4>{
        Vertex(0.5, -0.5, 0.5, 0, 0),
            Vertex(0.5, -0.5, -0.5, 1, 0),
            Vertex(0.5, 0.5, -0.5, 1, 1),
            Vertex(0.5, 0.5, 0.5, 0, 1)
    },
        std::array<unsigned int, 6>{0, 1, 2, 0, 2, 3},
        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 0)
    ));
    // Top (y = +0.5)
    faces.push_back(Face(
        std::array<Vertex, 4>{
        Vertex(-0.5, 0.5, 0.5, 0, 0),
            Vertex(0.5, 0.5, 0.5, 1, 0),
            Vertex(0.5, 0.5, -0.5, 1, 1),
            Vertex(-0.5, 0.5, -0.5, 0, 1)
    },
        std::array<unsigned int, 6>{0, 1, 2, 0, 2, 3},
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0)
    ));
    // Bottom (y = -0.5)
    faces.push_back(Face(
        std::array<Vertex, 4>{
        Vertex(-0.5, -0.5, -0.5, 0, 0),
            Vertex(0.5, -0.5, -0.5, 1, 0),
            Vertex(0.5, -0.5, 0.5, 1, 1),
            Vertex(-0.5, -0.5, 0.5, 0, 1)
    },
        std::array<unsigned int, 6>{0, 1, 2, 0, 2, 3},
        glm::vec3(0, -1, 0),
        glm::vec3(0, -1, 0)
    ));


	blockRegistry = std::make_unique<BlockRegistry>();

	blockRegistry->PushBlockData(BlockData("AIR", Model(std::vector<Face>()), false));
	blockRegistry->PushBlockData(BlockData("ROCK", Model(faces), true));
}


void Universe::Start()
{
	m_Camera = std::make_shared<Entity>("Camera");

    m_Camera->AddComponent(std::make_shared<Transform>(), "default");
    m_Camera->transform = m_Camera->GetComponent<Transform>();


    m_Camera->AddComponent(std::make_shared<Camera>());

	mainCamera = m_Camera;


	m_Chunk = std::make_shared<Chunk>(8, 8, this);
	m_Chunk->GenerateChunk();
	m_Chunk->GenerateChunkMesh();
}



void Universe::Render()
{
	m_Projection = glm::perspective(glm::radians(45.0f),(float)window->data.width/ (float)window->data.height, 0.1f, 100.0f);

	for(auto& system : m_RenderSystems)
	{
		system->Tick(std::vector<std::shared_ptr<Entity>>{m_Camera, m_Chunk});
	}
}

void Universe::Update(float deltaTime)
{
	for (auto& system : m_UpdateSystems)
	{
		system->Tick(std::vector<std::shared_ptr<Entity>>{m_Camera, m_Chunk});
	}

    if(glfwGetKey(window->GetGLFWWindow(), GLFW_KEY_W) == GLFW_PRESS)
    {
        m_Camera->transform->position += glm::vec3(0, 0, -1) * deltaTime * 5.f;
	}
    if (glfwGetKey(window->GetGLFWWindow(), GLFW_KEY_A) == GLFW_PRESS)
    {
        m_Camera->transform->position += glm::vec3(-1, 0, 0) * deltaTime * 5.f;
    }
    if (glfwGetKey(window->GetGLFWWindow(), GLFW_KEY_S) == GLFW_PRESS)
    {
        m_Camera->transform->position += glm::vec3(0, 0, 1) * deltaTime * 5.f;
    }
    if (glfwGetKey(window->GetGLFWWindow(), GLFW_KEY_D) == GLFW_PRESS)
    {
        m_Camera->transform->position += glm::vec3(1, 0, 0) * deltaTime * 5.f;
	}
    if (glfwGetKey(window->GetGLFWWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        m_Camera->transform->position += glm::vec3(0, 1, 0) * deltaTime * 5.f;
	}
    if (glfwGetKey(window->GetGLFWWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        m_Camera->transform->position += glm::vec3(0, -1, 0) * deltaTime * 5.f;
	}
}
