#pragma once
#include<vector>
#include<memory>

class Universe;
class Entity;

class System
{
public:
	System(Universe* universe)
	{
		this->universe = universe;
	}

	virtual ~System() = default;

	virtual void Tick(const std::vector<std::shared_ptr<Entity>>& entities) = 0;
	Universe* universe;
private:
};