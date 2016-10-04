#ifndef __SPHERES_H__
#define __SPHERES_H__

#include "MyMesh.h"
#include <math.h>

class Spheres{
public:
		MyMesh mesh;
		Spheres(float radius, int slices, int stacks);
		void initSpheres(char* fileName, const char* vFile, const char* fFile);
		void logic(glm::mat4 view,glm::mat4 projection);
		void draw(glm::mat4 view,glm::mat4 projection,glm::vec3 scale, glm::vec3 color);
		glm::vec3 position;
		int scale;
		float anglePath;
		

};

#endif
