#pragma once

#include"Component.h"



class ChunkComponent : public Component
{
public:
	ChunkComponent()
		:width(16), height(16)
	{
	}

	ChunkComponent(int width, int height)
		:width(width), height(height)
	{
	}

	int width;
	int height;
};
