#include <gl/glew.h>
#include <fbxsdk.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#include <stdio.h>
#include <cmath>
#include <FreeImage.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <list>
#include "CrashReporter.h"

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#define WINDOW_TITLE "RacingGame"

#define TEXTURES_SUBDIR "Textures/"
#define SHADERS_SUBDIR "Shaders/"
#define MODELS_SUBDIR "Models/"