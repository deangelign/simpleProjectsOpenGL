#ifndef __MIRROR_H__
#define __MIRROR_H__

#include "MyMesh.h"

class Mirror{
	
public:
	Mirror();
	MyMesh mesh;
	glm::vec3 position;
	void logic(glm::mat4 view,glm::mat4 projection,int scale);
	
	void loadMirror(char* textureFileName,const char* vertexShaderFileName, const char* FragmentShaderFileName );
	void generateMirror();
	void draw(glm::mat4 view,glm::mat4 projection,glm::vec3 scale, GLfloat alpha, glm::vec3 color);
	void logic(glm::mat4 view,glm::mat4 projection,glm::vec3 scale, GLfloat alpha, glm::vec3 color);
	

};




#endif
