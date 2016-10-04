#ifndef __MOUSEEVENTMANAGER_H__
#define __MOUSEEVENTMANAGER_H__

#include "Camera.h"
#include "cmath"


//angles mensured in rad

class MouseEventManager{
private:
	float sphereRadius;
	glm::vec2 sphereAngles;
	int mouseVariationX;
	int mouseVariationY;
	float mouseSpeed;
	glm::vec3 objectCoordinatesInSphere;
	
public:
	MouseEventManager();
	
	void setSphereRadius(float _sphereRadius);
	void setSphereAngles(glm::vec2 _sphereAngles);
	void setSphereAngle(int index, float angle);
	
	float getSphereRadius();
	glm::vec2 getSphereAngles();
	float getSphereAngle(int index);
	glm::vec3 getObjectCoordinatesInSphere();
	
	glm::vec3 motion(int x, int y,int screen_width,int screen_height);
	
};


#endif
