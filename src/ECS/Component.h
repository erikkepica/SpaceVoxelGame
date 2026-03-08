#pragma once
#include<string>

class Component
{
public:
	Component() = default;
	virtual ~Component() = default;

	std::string uniqueID = "none";
};