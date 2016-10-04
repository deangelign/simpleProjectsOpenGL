#ifndef __SOLDIER_H__
#define __SOLDIER_H__

#include "MyMesh.h"

class Soldier{
private:
	MyMesh mesh;
	glm::vec3 position;
	void logic(glm::mat4 view,glm::mat4 projection);
	
	
public:
	Soldier();
	
	//getters
	MyMesh getMesh();
	glm::vec3 getPosition();
	
	//setters
	void setMesh(MyMesh _mesh);
	void setPosition(glm::vec3 _position);
	
	void InitSoldierUsingGlmModel();
	void draw(glm::mat4 model, glm::mat4 view,glm::mat4 projection, glm::vec3 scale, float alpha, glm::vec3 color);
	
};


#endif

