#pragma once

#include"Face.h"
#include<vector>

class Model
{
	public:
	Model(std::vector<Face> faces)
		: faces(faces) {}

	std::vector<Face> faces;
};