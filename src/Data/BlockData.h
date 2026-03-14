#pragma once
#include"graphics/Model.h"
#include<string>

class BlockData
{
public:
	BlockData(std::string name, Model model, bool culling)
		:name(name), model(model), culling(culling) {
	}

	std::string name;
	Model model;
	bool culling = true;
};