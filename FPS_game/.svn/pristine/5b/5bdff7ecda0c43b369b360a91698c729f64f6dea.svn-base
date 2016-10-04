#ifndef __CAR_H__
#define __CAR_H__

#include "MyMesh.h"

class Car{
private:
	MyMesh mesh;
	glm::vec3 position;
	void logic(glm::mat4 view,glm::mat4 projection);
	
	
public:
	Car();
	
	//getters
	MyMesh getMesh();
	glm::vec3 getPosition();
	
	//setters
	void setMesh(MyMesh _mesh);
	void setPosition(glm::vec3 _position);
	void setPositionCoordinate(int index, GLfloat coordinateValue);
	
	void InitCarUsingGlmModel();
	void draw(glm::mat4 model, glm::mat4 view,glm::mat4 projection, glm::vec3 scale, float alpha, glm::vec3 color);
	
	void mode(glm::vec3 distance);
	
	

};

#endif

