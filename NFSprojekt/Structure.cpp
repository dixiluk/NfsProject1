#include "Structure.h"

std::list<Structure*> Structure::Structures;


Structure::Structure(glm::vec3 position, Model* model, Shader* shader) : StaticObject()
{
	this->position = position;
	this->model = model;
	this->shader = shader;
	Structures.push_back(this);
}

Structure::~Structure()
{
}

void Structure::draw(Shader *shad)
{
	this->shader->onPrepare(this);

	for (std::list<ModelObject*>::iterator it = this->model->objects.begin();
		it != this->model->objects.end(); it++){

		ModelObject* obj = *it;
		this->shader->onDraw(obj);
		glBindVertexArray(obj->arrayBuffer);
		glDrawElements(GL_TRIANGLES, obj->verticesCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

	}
}
