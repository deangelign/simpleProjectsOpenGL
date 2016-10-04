#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include "MyMesh.h"

class SkyBox{
private:
	MyMesh mesh;
	glm::vec3 position;
	void logic(glm::mat4 view,glm::mat4 projection,glm::vec3 scale);
	char* frontTextureFileName;
	char* backTextureFileName; 
	char* leftTextureFileName;
	char* rightTextureFileName;
	char* topTextureFileName;
	char* bottomTextureFileName; 
	
	void generateCube();
	
	GLsizeiptr sizeVectorVertice ;
	GLsizeiptr sizeVectorNormal;
	GLsizeiptr sizeVectorElements;
	GLsizeiptr sizeVectorTextureCoord;
	GLsizeiptr total;
	
public:
	SkyBox();
	
	//getters
	MyMesh getMesh();
	glm::vec3 getPosition();
	//setters
	void setMesh(MyMesh _mesh);
	void setPosition(glm::vec3 _position);
	
	void loadSkyBox(char* _frontTextureFileName, char* backTextureFileName,char* leftTextureFileName,char* rightTextureFileName,char* topTextureFileName);
	void draw(glm::mat4 view,glm::mat4 projection,glm::vec3 scale,int cameraIndex);
	
};

#endif
