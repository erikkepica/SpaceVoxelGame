#pragma once
#include"Entity.h"

#include"ChunkComponent.h"

#include"Renderer.h"

#include"ECS/Block.h"

class Chunk : public Entity
{
public:
	Chunk(int width, int height);

	//TODO make a seperate world generation system (maybe with components)
	void GenerateChunk();
	void GenerateChunkMesh();

	std::shared_ptr<ChunkComponent> chunkComponent;
	std::shared_ptr<Renderer> renderer;

	Block GetBlock(int x, int y, int z);

private:
	std::vector<Block> m_Blocks;
};