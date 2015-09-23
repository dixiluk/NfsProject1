#include "Environment.h"
#include "Engine.h"
#include "Structure.h"
#include "Environment.h"
#include "Camera.h"
#include "ModelObject.h"

int main(int argc, char * argv[])
{
	Engine::Instance = new Engine(Engine::Resolution(1440, 900));

	Engine::Init(argc, argv);

	Scene* scene = new Scene();

	Engine::Instance->activeScene = (Scene*)scene;

	glutMainLoop();

	return 0;
}