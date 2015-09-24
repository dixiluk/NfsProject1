#pragma once
#include "GraphicalObject.h"

class DynamicObject : GraphicalObject
{
public:
	DynamicObject();
	~DynamicObject();
	void draw(Shader* shad = 0);
};

