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
	GLfloat* v, *uv, *n, *tan, *btan, *aI, *aW;
	const char* name;
	int verticesCount;
	glm::vec3 relativePosition;
	Texture *diffuseMap, *normalMap;
	GLuint arrayBuffer;
	void computeTangents();
	void createArrayBuffer();
	void extractMesh(FbxNode* node);
	void extractBones(FbxNode* node);
	ModelObject(FbxNode* node);
	~ModelObject();
};

