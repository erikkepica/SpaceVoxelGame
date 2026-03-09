#pragma once
#include<string>
#include<memory>
#include<vector>

#include"Component.h"
#include"Transform.h"

class Entity
{
public:
	Entity();
	Entity(std::string name);

	std::string name;

	void AddComponent(std::shared_ptr<Component> component);
	void AddComponent(std::shared_ptr<Component> component, std::string uniqueID);
	template<typename T>
	std::shared_ptr<T> GetComponent();

	std::shared_ptr<Transform> transform; // Default transform component
private:
	std::vector<std::shared_ptr<Component>> m_Components;
};


template<typename T>
inline std::shared_ptr<T> Entity::GetComponent()
{
	for (auto& c : m_Components)
	{
		if (std::dynamic_pointer_cast<T>(c))
		{
			return std::dynamic_pointer_cast<T>(c);
		}
	}
	return nullptr;
}