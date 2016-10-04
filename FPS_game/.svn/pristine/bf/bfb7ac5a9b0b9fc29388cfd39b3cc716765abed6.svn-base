#ifndef __GUN_H__
#define __GUN_H__

#include "MyMesh.h"

class Gun{
private:
	MyMesh mesh;
	glm::vec3 position;
	void logic(glm::mat4 view,glm::mat4 projection);
	
	
public:
	Gun();
	
	//getters
	MyMesh getMesh();
	glm::vec3 getPosition();
	
	//setters
	void setMesh(MyMesh _mesh);
	void setPosition(glm::vec3 _position);
	
	void InitGunUsingGlmModel();
	void draw(glm::mat4 model, glm::mat4 view,glm::mat4 projection, glm::vec3 scale, float alpha, glm::vec3 color);
	
};


#endif
