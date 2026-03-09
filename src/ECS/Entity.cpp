#include "Entity.h"

Entity::Entity()
{
	this->name = "none";
}

Entity::Entity(std::string name)
{
	this->name = name;
}

void Entity::AddComponent(std::shared_ptr<Component> component)
{
	m_Components.push_back(component);
}

void Entity::AddComponent(std::shared_ptr<Component> component, std::string uniqueID)
{
	component->uniqueID = uniqueID;
	m_Components.push_back(component);
}

