#include "MouseEventManager.h"
#include <iostream>

using namespace std;

//default constructor
MouseEventManager::MouseEventManager(){
	sphereRadius = 1.; 
	sphereAngles.x = 0;
	sphereAngles.y = 0;
	mouseVariationX = 0;
	mouseVariationY = 0;
	mouseSpeed = 0.001;
	objectCoordinatesInSphere = glm::vec3(0.0,1.0,1.0);
}

void MouseEventManager::setSphereRadius(float _sphereRadius){
	this->sphereRadius = _sphereRadius;
}

void MouseEventManager::setSphereAngles(glm::vec2 _sphereAngles){
	this->sphereAngles = _sphereAngles;
}

void MouseEventManager::setSphereAngle(int index, float angle){
	if(index == 0){
		this->sphereAngles.x = angle;
	}
	else if(index == 1){
		this->sphereAngles.y = angle;
	}
	else{
		cout << "Mouse1: invalid index for sphere angles" << endl;
	}
}

float MouseEventManager::getSphereRadius(){
	return this->sphereRadius;
}

glm::vec2 MouseEventManager::getSphereAngles(){
	return this->sphereAngles;
}
	
float MouseEventManager::getSphereAngle(int index){
	if(index == 0){
		return this->sphereAngles.x;
	}
	else if(index == 1){
		return this->sphereAngles.y;
	}
	else{
		cout << "Mouse2: invalid index for sphere angles" << endl;
		return 0;
	}
	
	
}


//calculate the direction of character's vision
glm::vec3 MouseEventManager::motion(int x, int y,int screen_width,int screen_height){
	static int wrap = 0;
	
	
	if(!wrap) {
 
		mouseVariationX = x - (screen_width/2);
		mouseVariationY = y - (screen_height/2);
	 
		wrap = 1;
		glutWarpPointer(screen_width/ 2, screen_height / 2); // move mouse pointer back to the center of the window
	} 
	else {
		wrap = 0;
	}

	//calculating the sphere angles
    this->sphereAngles.x += mouseVariationX * mouseSpeed;
    this->sphereAngles.y += mouseVariationY * mouseSpeed;
	
	//cout << this->sphereAngles.x  << endl;
	//cout << this->sphereAngles.y  << endl;
 
    if(this->sphereAngles.x < -M_PI){
      this->sphereAngles.x += M_PI * 2;
	}
    else if(this->sphereAngles.x > M_PI){
      this->sphereAngles.x -= M_PI * 2;
	}
	
    if(this->sphereAngles.y < -M_PI / 2){
      this->sphereAngles.y = (-M_PI / 2)+(M_PI/180);
	}
    
    if(this->sphereAngles.y > M_PI / 2){
	  this->sphereAngles.y = (M_PI / 2)-(M_PI/180);
	}
    
    this->objectCoordinatesInSphere = glm::vec3( sphereRadius*sin(sphereAngles.x) * cos(sphereAngles.y), sphereRadius*sin(sphereAngles.y), sphereRadius*cos(sphereAngles.x) * cos(sphereAngles.y));
	return objectCoordinatesInSphere;
	
}

glm::vec3 MouseEventManager::getObjectCoordinatesInSphere(){
	return this->objectCoordinatesInSphere;
}
