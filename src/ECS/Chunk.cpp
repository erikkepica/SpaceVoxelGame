#include"Chunk.h"
#include"Block.h"


Chunk::Chunk(int width, int height)
	:Entity("Chunk")
{
	AddComponent(std::make_shared<Transform>(), "default");
	transform = GetComponent<Transform>();

	AddComponent(std::make_shared<Renderer>());
	renderer = GetComponent<Renderer>();

	AddComponent(std::make_shared<ChunkComponent>());
	chunkComponent = GetComponent<ChunkComponent>();
}

void Chunk::GenerateChunk()
{
	m_Blocks.clear();
	for(int x = 0; x < chunkComponent->width; x++)
	{
		for (int z = 0; z < chunkComponent->width; z++)
		{
			for(int y = 0; y < chunkComponent->height; y++)
			{
				if (y > x)
				{
					m_Blocks.push_back(Block("AIR"));
				}
				m_Blocks.push_back(Block("ROCK"));
			}
		}
	}
}

void Chunk::GenerateChunkMesh()
{
	std::vector<float> vertices;
	std::vector<UINT> indices;

	std::vector<float> vertices_
	{

		-.5f,-.5f, 0.f, 0.0f, 0.0f,
		 .5f,-.5f, 0.f, 1.0f, 0.0f,
		 .5f, .5f, 0.f, 1.0f, 1.0f,
		-.5f, .5f, 0.f, 0.0f, 1.0f

	};
	std::vector<UINT> indices_
	{

	0,1,2,
	0,2,3

	};
	int c = 0;
	for (int x = 0; x < chunkComponent->width; x++)
	{
		for (int z = 0; z < chunkComponent->width; z++)
		{
			for (int y = 0; y < chunkComponent->height; y++)
			{
				c++;
				if(GetBlock(x,y,z).name != "AIR")
				{
					for(int i = 0; i < vertices_.size(); i+=5)
					{
						vertices.push_back(vertices_[i] + x);
						vertices.push_back(vertices_[i+1] + y);
						vertices.push_back(vertices_[i+2] + z);
					}
					for(int i : indices_)
					{
						indices.push_back(i+c);
					}
				}
			}
		}
	}

	renderer->vertices = vertices;
	renderer->indices = indices;

	VertexBufferLayout vbl;
	vbl.Push<float>(3);
	vbl.Push<float>(2);

	renderer->CreateMesh(vbl);

	renderer->shader.Generate(RESOURCES_PATH "vertex.vert", RESOURCES_PATH "fragment.frag");

	renderer->texture.Generate(RESOURCES_PATH "penguin.png");
}

Block Chunk::GetBlock(int x, int y, int z)
{
	return m_Blocks[y * chunkComponent->width * chunkComponent->width + z * chunkComponent->width + x];
}
