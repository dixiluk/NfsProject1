#include "Structure.h"

std::list<Structure*> Structure::Structures;


Structure::Structure() : StaticObject()
{
	Structures.push_back(this);
}

Structure::~Structure()
{
}

void Structure::draw(Shader *shad)
{
	if (shad == 0)
		shad = this->shader;
	shad->onPrepare(this);

	for (std::list<ModelObject*>::iterator it = this->model->objects.begin();
		it != this->model->objects.end(); it++){

		ModelObject* obj = *it;
		shad->onDraw(obj);
		glBindVertexArray(obj->arrayBuffer);
		glDrawElements(GL_TRIANGLES, obj->verticesCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

	}
}
