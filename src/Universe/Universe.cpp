#include"Universe/Universe.h"
#include <glm/gtc/matrix_transform.hpp>

#include"ECS/Transform.h"
#include"ECS/Renderer.h"


glm::mat4 m_Model = glm::mat4(1.0f);
glm::mat4 m_View = glm::mat4(1.0f);
glm::mat4 m_Projection = glm::mat4(1.0f);

Universe::Universe()
{
	Start();
}

void Universe::Start()
{
	m_Entity.AddComponent(std::make_shared<Transform>(), "default");
	m_Entity.transform = m_Entity.GetComponent<Transform>();



	m_Entity.AddComponent(std::make_shared<Renderer>());




	m_Entity.GetComponent<Renderer>()->VAO.Generate();
	m_Entity.GetComponent<Renderer>()->VBO.Generate(m_Entity.GetComponent<Renderer>()->vertices);
	m_Entity.GetComponent<Renderer>()->EBO.Generate(m_Entity.GetComponent<Renderer>()->indices);

	VertexBufferLayout vbl;
	vbl.Push<float>(3);
	vbl.Push<float>(2);

	m_Entity.GetComponent<Renderer>()->VAO.DoAttribs(vbl);

	VBO::UnBind();
	VAO::Unbind();
	EBO::UnBind();

	//m_Entity.GetComponent<Renderer>()->shader.Generate(RESOURCES_PATH "raymarching.vert", RESOURCES_PATH "raymarching.frag");
	m_Entity.GetComponent<Renderer>()->shader.Generate(RESOURCES_PATH "vertex.vert", RESOURCES_PATH "fragment.frag");

	m_Entity.GetComponent<Renderer>()->texture.Generate(RESOURCES_PATH "penguin.png");

	m_View = glm::translate(m_View, glm::vec3(0.0f, 0.0f, -3.0f));
}



void Universe::Render(WindowData windowData)
{
	m_Projection = glm::perspective(glm::radians(45.0f),(float)windowData.width/ (float)windowData.height, 0.1f, 100.0f);


	m_Entity.GetComponent<Renderer>()->EBO.Bind();
	m_Entity.GetComponent<Renderer>()->VAO.Bind();

	m_Entity.GetComponent<Renderer>()->shader.Use();

	m_Entity.GetComponent<Renderer>()->shader.SetMat4("model", m_Model);
	m_Entity.GetComponent<Renderer>()->shader.SetMat4("view", m_View);
	m_Entity.GetComponent<Renderer>()->shader.SetMat4("projection", m_Projection);

	m_Entity.GetComponent<Renderer>()->shader.SetVec2("resolution", glm::vec2(windowData.width, windowData.height));

	m_Entity.GetComponent<Renderer>()->texture.Bind();

	glDrawElements(GL_TRIANGLES, m_Entity.GetComponent<Renderer>()->EBO.GetIndicesNum(), GL_UNSIGNED_INT, 0);

	VAO::Unbind();
	EBO::UnBind();
}

void Universe::Update(float deltaTime)
{
	m_Model = glm::mat4(1.0f);

	m_Model = glm::translate(m_Model, m_Entity.GetComponent<Transform>()->position);

	m_Model = glm::rotate(m_Model, glm::radians(m_Entity.transform->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	m_Model = glm::rotate(m_Model, glm::radians(m_Entity.transform->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	m_Model = glm::rotate(m_Model, glm::radians(m_Entity.transform->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	m_Model = glm::scale(m_Model, m_Entity.transform->scale);
}
