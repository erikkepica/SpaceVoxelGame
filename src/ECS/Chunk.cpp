#include"Chunk.h"
#include"Block.h"


Chunk::Chunk(int width, int height, Universe* universe)
	:Entity("Chunk"), universe(universe)
{
	AddComponent(std::make_shared<Transform>(), "default");
	transform = GetComponent<Transform>();

	AddComponent(std::make_shared<Renderer>());
	renderer = GetComponent<Renderer>();

	AddComponent(std::make_shared<ChunkComponent>(width,height));
	chunkComponent = GetComponent<ChunkComponent>();
}

void Chunk::GenerateChunk()
{
	m_Blocks.clear();
	for(int x = 0; x < chunkComponent->width; x++)
	{
		for (int y = 0; y < chunkComponent->height; y++)
		{
			for(int z = 0; z < chunkComponent->width; z++)
			{
				if (y > z)
				{
					m_Blocks.push_back(universe->blockRegistry->GetBlockID("AIR"));
				}
				else
				{
					m_Blocks.push_back(universe->blockRegistry->GetBlockID("ROCK"));
				}
			}
		}
	}
}

void Chunk::GenerateChunkMesh()
{
	std::vector<float> vertices;
	std::vector<UINT> indices;

	int c = 0;
	for (int x = 0; x < chunkComponent->width; x++) {
		for (int y = 0; y < chunkComponent->height; y++) {
			for (int z = 0; z < chunkComponent->width; z++) {
				const auto& blockData = universe->blockRegistry->GetBlockData(GetBlock(x, y, z));
				if (blockData.model.faces.empty()) continue;

				for (int f = 0; f < blockData.model.faces.size(); f++) {
					const auto& face = blockData.model.faces[f];
					int cx = x + (int)face.cullNormal.x;
					int cy = y + (int)face.cullNormal.y;
					int cz = z + (int)face.cullNormal.z;

					bool outside = cx < 0 || cx >= chunkComponent->width ||
						cy < 0 || cy >= chunkComponent->height ||
						cz < 0 || cz >= chunkComponent->width;
					if (!outside) {
						if (universe->blockRegistry->GetBlockData(GetBlock(cx, cy, cz)).culling) continue;
					}

					for (int i = 0; i < 4; i++) {
						vertices.push_back(face.vertices[i].x + x);
						vertices.push_back(face.vertices[i].y + y);
						vertices.push_back(face.vertices[i].z + z);
						vertices.push_back(face.normal.x);
						vertices.push_back(face.normal.y);
						vertices.push_back(face.normal.z);
						vertices.push_back(face.vertices[i].u);
						vertices.push_back(face.vertices[i].v);
					}
					for (int j : face.indices) indices.push_back(j + c);
					c += 4;
				}
			}
		}
	}

	renderer->vertices = vertices;
	renderer->indices = indices;

	VertexBufferLayout vbl;
	vbl.Push<float>(3);
	vbl.Push<float>(3);
	vbl.Push<float>(2);

	renderer->CreateMesh(vbl);

	renderer->shader.Generate(RESOURCES_PATH "vertex.vert", RESOURCES_PATH "fragment.frag");

	renderer->texture.Generate(RESOURCES_PATH "head.png");
}

unsigned int Chunk::GetBlock(int x, int y, int z)
{
	return m_Blocks[x + chunkComponent->width * (y + chunkComponent->height * z)];
}
