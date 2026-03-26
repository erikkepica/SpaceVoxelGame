#pragma once
#include"Component.h"

#include"Entity.h"
#include<vector>

class BodyComponent : public Component
{
public:
	BodyComponent() {}

	int bodySize = 128;

	int chunkSize = 16;

	std::vector<std::shared_ptr<Entity>> chunks;
};