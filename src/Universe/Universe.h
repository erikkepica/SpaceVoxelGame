#pragma once

#include"Application/Application.h"

#include"ECS/Entity.h"

class Universe
{
public:
	Universe();

	void Start();

	void Render(WindowData windowData);
	
	void Update(float deltaTime);



private:
	Entity m_Entity = Entity("TestEntity");
};