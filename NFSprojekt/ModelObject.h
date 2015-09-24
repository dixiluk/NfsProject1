#pragma once
#include "Environment.h"

#include "Texture.h"

#define private public

class ModelObject
{
	friend class Model;
	friend class Structure;
	friend class DynamicObject;
private:
	GLfloat* v, *uv, *n;
	const char* name;
	int verticesCount;
	glm::vec3 relativePosition;
	Texture *diffuseMap;
	GLuint arrayBuffer;
	void createArrayBuffer();
	void extractMesh(FbxNode* node);
	ModelObject(FbxNode* node);
	~ModelObject();
};

