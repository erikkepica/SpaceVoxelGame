#pragma once
#include "Component.h"

#include"graphics/ShaderClass.h"
#include"graphics/Texture.h"

#include"graphics/ElementBufferObject.h"
#include"graphics/VertexArrayObject.h"
#include"graphics/VertexBufferObject.h"


class Renderer : public Component
{
public:
	Renderer()
	{}
	Renderer(std::vector<float> vertices, std::vector<UINT> indices)
	{
		this->vertices = vertices;
		this->indices = indices;	
	}

	void CreateMesh(VertexBufferLayout vbl)
	{
		VAO.Generate();
		VBO.Generate(vertices);
		EBO.Generate(indices);

		VAO.DoAttribs(vbl);

		VBO::UnBind();
		VAO::Unbind();
		EBO::UnBind();
	}

	std::vector<float> vertices
	{

		-.5f,-.5f, 0.f, 0.0f, 0.0f,
		 .5f,-.5f, 0.f, 1.0f, 0.0f,
		 .5f, .5f, 0.f, 1.0f, 1.0f,
		-.5f, .5f, 0.f, 0.0f, 1.0f

	};
	std::vector<UINT> indices
	{

	0,1,2,
	0,2,3

	};

	VAO VAO;
	VBO VBO;
	EBO EBO;

	Shader shader;
	Texture texture;
};