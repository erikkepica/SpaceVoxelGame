#pragma once
#include"System.h"

#include"ECS/Renderer.h"
#include"ECS/Sun.h"

class SunSystem : public System
{
	public:
	SunSystem(Universe* universe) : System(universe)
	{
	}
	virtual void Tick(const std::vector<std::shared_ptr<Entity>>& entities) override;

private:
	void Render(std::shared_ptr<Renderer> renderer, std::shared_ptr<Sun> sun);
};