#pragma once
#include"Entity.h"

#include"ChunkComponent.h"

#include"Renderer.h"

#include"ECS/Block.h"

#include"Body.h"

class Chunk : public Entity
{
public:

	Chunk(){}
	Chunk(int width, int height, Body* body);

	//TODO make a seperate world generation system (maybe with components)
	void GenerateChunk();
	void GenerateChunkMesh();

	std::shared_ptr<ChunkComponent> chunkComponent;
	std::shared_ptr<Renderer> renderer;

	unsigned int GetBlock(int x, int y, int z);

	Body* body = nullptr;

	glm::vec3 relativePosition = glm::vec3(0, 0, 0);

private:
	std::vector<unsigned int> m_Blocks;
};