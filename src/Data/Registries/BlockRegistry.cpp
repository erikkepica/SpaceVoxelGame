#include "BlockRegistry.h"

void BlockRegistry::PushBlockData(BlockData data)
{
	m_BlockDataMap.push_back(data);
}

uint16_t BlockRegistry::GetBlockID(std::string name)
{
	for (size_t i = 0; i < m_BlockDataMap.size(); i++)
	{
		if (m_BlockDataMap[i].name == name)
		{
			return i;
		}
	}
	return 0;
}

BlockData BlockRegistry::GetBlockData(std::string name)
{
	return m_BlockDataMap[GetBlockID(name)];
}

BlockData BlockRegistry::GetBlockData(uint16_t ID)
{
	return m_BlockDataMap[ID];
}
