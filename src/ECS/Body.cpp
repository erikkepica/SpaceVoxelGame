#include "Body.h"

#include"BodyComponent.h"
#include"Chunk.h"

Body::Body(std::string name, Universe* universe)
	:Entity(name), universe(universe)
{
	AddComponent(std::make_shared<Transform>(), "default");
	transform = GetComponent<Transform>();

	AddComponent(std::make_shared<BodyComponent>(), "default");
	body = GetComponent<BodyComponent>();
}

void Body::Generate()
{
	body->chunks.clear();
	int numChunks = body->bodySize / body->chunkSize *2;
	for (int x = 0; x < numChunks; x++)
	{
		for (int y = 0; y < numChunks; y++)
		{
			for (int z = 0; z < numChunks; z++)
			{
				std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(body->chunkSize, body->chunkSize, this);
				chunk->transform->position = glm::vec3(x * body->chunkSize, y * body->chunkSize, z * body->chunkSize) + transform->position;
				chunk->relativePosition = glm::vec3(x * body->chunkSize, y * body->chunkSize, z * body->chunkSize);
				chunk->GenerateChunk();
				chunk->GenerateChunkMesh();
				body->chunks.push_back(chunk);
			}
		}
	}
}
