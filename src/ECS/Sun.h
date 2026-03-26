#pragma once
#include"Component.h"

#include<glm/glm.hpp>

class Sun : public Component
{
public:
	Sun() {}
	

	float sunIntensity;
	float sunTemperature;
	
	float sunRadius;
	glm::vec3 sunPos;
};