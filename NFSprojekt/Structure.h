#pragma once
#include "Model.h"
#include "StaticObject.h"

class Structure : public StaticObject
{
public:
	static std::list<Structure*> Structures;
	Structure();
	~Structure();
	Model* model;
	glm::mat4 iModelMat;
protected:
	void draw(Shader* shad = 0);

};
