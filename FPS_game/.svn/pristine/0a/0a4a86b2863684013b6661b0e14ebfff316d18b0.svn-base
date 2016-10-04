#ifndef __KEYBOARDEVENTMANAGER_H__
#define __KEYBOARDEVENTMANAGER_H__

#include "Camera.h"
#include "Car.h"
#include "MouseEventManager.h"

class KeyBoardEventManager{
private:
	int left ; 
	int right;
	int foward ; 
	int backward ; 
	int move;
	float moveSpeed;
	glm::vec3 forward_dir;
	glm::vec3 right_dir;
	

	
public:
	
	KeyBoardEventManager();
	void eventKey(unsigned char keyCode,int x, int y,Car car, Camera *camera, MouseEventManager *mouse);
	void eventUpKey(unsigned char keyCode,int x, int y,Car car, Camera *camera);
	void CalculateMovimentVectors(Camera* camera,float sphereAngle1, int time,glm::vec3 cubeLimitP, glm::vec3 cubeLimitN, float theshold);
	void CalculateMovimentVectors(Car* car,float sphereAngle1, int time,glm::vec3 cubeLimitP, glm::vec3 cubeLimitN, float theshold);
	float calculateDistance(glm::vec3 a,glm::vec3 b);
	
	int movingLeft();
	int movingRight();
	int movingFoward();
	int movingBackward();
	
	
	void jump(Camera* camera);
	
	int numCameras;
	int cameraIndex;
	int isEscape;
	int isJumping;
	int isJumpingUp;
	int isJumpingDown;
	float jumpSpeed;
	float jumpLimit;
	float dy;
	int isDriving;
	
};

#endif

