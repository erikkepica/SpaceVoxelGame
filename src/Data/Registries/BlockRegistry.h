#pragma once
#include"Data/BlockData.h"

class BlockRegistry
{
public:

	void PushBlockData(BlockData data);

	uint16_t GetBlockID(std::string name);
	BlockData GetBlockData(std::string name);
	BlockData GetBlockData(uint16_t ID);

private:
	std::vector<BlockData> m_BlockDataMap;
};