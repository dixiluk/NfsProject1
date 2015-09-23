#pragma once
#include "Environment.h"

class GraphicalObject
{
	friend class Engine;
public:
	GraphicalObject();
	~GraphicalObject();
protected:
	glm::vec3 position;
	glm::vec3 rotationAxis;
	double rotationPower;

	virtual void compute();
	virtual void draw();
};

