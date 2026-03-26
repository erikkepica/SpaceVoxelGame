#include"Universe/Universe.h"
#include <glm/gtc/matrix_transform.hpp>

#include"ECS/Entity.h"

#include"ECS/Transform.h"
#include"ECS/Renderer.h"
#include"ECS/Camera.h"
#include"ECS/Sun.h"

#include"Systems/RenderSystem.h"
#include"Systems/SunSystem.h"

#include"ECS/Body.h"

#include <algorithm>

Universe::Universe(std::shared_ptr<Window> window)
{
	this->window = window;

	m_RenderSystems.push_back(std::make_unique<RenderSystem>(this));
	m_RenderSystems.push_back(std::make_unique<SunSystem>(this));

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

float speed = 1.0f;


void Universe::Start()
{

    glfwSetScrollCallback(window->GetGLFWWindow(), [](GLFWwindow* window, double xoffset, double yoffset) {
		speed += (float)yoffset;
		if (speed < 0.1f) speed = 0.1f;
		});

	m_Sun = std::make_shared<Entity>("Sun");

	m_Sun->AddComponent(std::make_shared<Sun>());
	m_Sun->GetComponent<Sun>()->sunPos = glm::vec3(0, 0, -100000);
	m_Sun->GetComponent<Sun>()->sunRadius = 10000;
	m_Sun->GetComponent<Sun>()->sunIntensity = 100;

    m_Sun->AddComponent(std::make_shared<Renderer>());

    m_Sun->GetComponent<Renderer>()->vertices = {
        -1.0f, -1.0f, 0.f, 0.0f, 0.0f,
        1.0f, -1.0f, 0.f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.f, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.f, 0.0f, 1.0f
	};

    m_Sun->GetComponent<Renderer>()->indices = {
        0, 1, 2,
        0, 2, 3
	};

	mainSun = m_Sun;

    VertexBufferLayout vbl;
    vbl.Push<float>(3);
    vbl.Push<float>(2);

	m_Sun->GetComponent<Renderer>()->CreateMesh(vbl);

    m_Sun->GetComponent<Renderer>()->shader.Generate(RESOURCES_PATH "shaders/sun.vert", RESOURCES_PATH "shaders/sun.frag");


	m_Camera = std::make_shared<Entity>("Camera");

    m_Camera->AddComponent(std::make_shared<Transform>(), "default");
    m_Camera->transform = m_Camera->GetComponent<Transform>();

    m_Camera->AddComponent(std::make_shared<Camera>());

	mainCamera = m_Camera;
	mainCamera->GetComponent<Camera>()->SetProjection((float)window->data.width / (float)window->data.height);

    m_Asteroid = std::make_shared<Body>("Asteroid", this);
    m_Asteroid->Generate();
}



void Universe::Render()
{
	for(auto& system : m_RenderSystems)
	{
		system->Tick(std::vector<std::shared_ptr<Entity>>{m_Camera, m_Sun});
		system->Tick(m_Asteroid->body->chunks);
	}
}

double g_LastMouseX = 0;
double g_LastMouseY = 0;



void Universe::Update(float deltaTime)
{
	for (auto& system : m_UpdateSystems)
	{
		system->Tick(std::vector<std::shared_ptr<Entity>>{m_Camera});
        system->Tick(m_Asteroid->body->chunks);
	}

	float t = sin((float)glfwGetTime()) * 0.5f + 0.5f; // oscillates between 0 and 1

    mainSun->GetComponent<Sun>()->sunTemperature = STAR_TYPES[2].temperature;

    double mouseX, mouseY;
    
    glfwGetCursorPos(window->GetGLFWWindow(), &mouseX, &mouseY);
    
    double dx = mouseX - g_LastMouseX;
    double dy = mouseY - g_LastMouseY;

	g_LastMouseX = mouseX;
	g_LastMouseY = mouseY;

	m_Camera->transform->rotation.y += dx * 0.1f;
	m_Camera->transform->rotation.x += dy * 0.1f;

    m_Camera->transform->rotation.x = glm::clamp(m_Camera->transform->rotation.x, -90.0f, 90.0f);

    glm::vec3 forward = m_Camera->transform->Forward();
    glm::vec3 right = m_Camera->transform->Right();
    glm::vec3 up = glm::vec3(0, 1, 0); // world up for SPACE/SHIFT


    if (glfwGetKey(window->GetGLFWWindow(), GLFW_KEY_W) == GLFW_PRESS)
        m_Camera->transform->position += forward * deltaTime * 5.f * speed;

    if (glfwGetKey(window->GetGLFWWindow(), GLFW_KEY_S) == GLFW_PRESS)
        m_Camera->transform->position -= forward * deltaTime * 5.f * speed;

    if (glfwGetKey(window->GetGLFWWindow(), GLFW_KEY_A) == GLFW_PRESS)
        m_Camera->transform->position -= right * deltaTime * 5.f * speed;

    if (glfwGetKey(window->GetGLFWWindow(), GLFW_KEY_D) == GLFW_PRESS)
        m_Camera->transform->position += right * deltaTime * 5.f * speed;

    if (glfwGetKey(window->GetGLFWWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
        m_Camera->transform->position += up * deltaTime * 5.f * speed;

    if (glfwGetKey(window->GetGLFWWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        m_Camera->transform->position -= up * deltaTime * 5.f * speed;

}
