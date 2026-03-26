#pragma once
#include"Entity.h"
#include"Universe/Universe.h"
#include"BodyComponent.h"

class Body : public Entity
{
public:
	Body(){}
	Body(std::string name, Universe* universe);

	std::shared_ptr<BodyComponent> body;

	Universe* universe = nullptr;

	void Generate();
private:

};
