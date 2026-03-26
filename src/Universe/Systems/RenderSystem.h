#pragma once
#include"Universe/Systems/System.h"

#include"ECS/Renderer.h"
#include"ECS/Transform.h"

class RenderSystem : public System
{
public:
	RenderSystem(Universe* universe) : System(universe)
	{
	}

	virtual void Tick(const std::vector<std::shared_ptr<Entity>>& entities) override;


private:
	void Render(std::shared_ptr<Renderer> renderer); // Render without transform, for UI elements
	void Render(std::shared_ptr<Renderer> renderer, std::shared_ptr<Transform> transform);
};