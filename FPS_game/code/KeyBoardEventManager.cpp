#include "KeyBoardEventManager.h"
#include <iostream>

using namespace std;

//to create the character moviment I defined 4 mask for each direction
//Using the funcIdle I check the keyEvent in "real time" 


//default constructor
KeyBoardEventManager::KeyBoardEventManager(){
	
	
	////define masks
	left = 1; 
	right = 2;
	foward = 4; 
	backward = 8;
	/////
	
	////variable that will be used in a bitwise operation with the masks
	move = 0;
	
	////how far the character goes 
	moveSpeed = 10;
	
	isJumping = 0; //"boolean" which checks if the the character in jumping
	jumpSpeed = 0.11;
	jumpLimit = 2; //maximum jump height 
	isJumpingUp = 0;//"boolean" that checks if the character is going up
	isJumpingDown = 0;//"boolean" that checks if the character is going down
	dy = 0;
	isEscape = 0;  //"boolean" that checks if the esc key pressed
	cameraIndex = 0; // 0 - normal view.....1-sky-view
	numCameras = 2;  
	isDriving = 0; //"is the character driving? 0-no 1-yes"
}


//this method evaluates the keyboard events
void KeyBoardEventManager::eventKey(unsigned char keyCode, int x, int y, Car car, Camera *camera,MouseEventManager *mouse){
	
	if(keyCode == 'a' || keyCode =='A') {;
		move |= left;  //bitwise operation with the mask left (OR operation)
		
	}

	if(keyCode == 'd' || keyCode == 'D'){
		move |= right; //bitwise operation with the mask Right (OR operation)
	}

	if(keyCode == 's' || keyCode == 'S'){
		move |= backward;  //bitwise operation with the mask backward (OR operation)
	}
	if(keyCode == 'w' || keyCode == 'W'){
		move |= foward;  //bitwise operation with the mask foward (OR operation)
	}
	
	
	if(keyCode == 'e' || keyCode == 'E'){
		if(isDriving){//if you are already inside the car
			isDriving = 0; //get out from the car
			
		}
		else{
			//check the distance between the character and the car
			glm::vec3 a = car.getPosition(); 
			glm::vec3 b = glm::vec3(camera->getEyeCoordinate(0),camera->getEyeCoordinate(1),camera->getEyeCoordinate(2));
			float distance = calculateDistance(a,b);
			//////
			if(distance <= 2){//is the character near to car? 
				isDriving = 1;//get in the car
				mouse->setSphereAngle(0,0);
				mouse->setSphereAngle(1,0);
				camera->setEyeCoordinates(a.x,a.y,a.z);
			}
		}
	}
	
	if(keyCode == 32){//Space
		if(isJumpingDown == 0){//is the character on the floor?
			isJumpingUp = 1;
		}
	}
	
	if(keyCode == 27){
		isEscape = 1;
	}
	
	if(keyCode == 'u' || keyCode == 'U'){//change the index camera
		cameraIndex++;
		if(cameraIndex >= numCameras ){
			cameraIndex = 0;
		}
	}
		

}

//calculate the distance bewteen the point a and b
//I used this method to calculate the distance between the character and the car
float KeyBoardEventManager::calculateDistance(glm::vec3 a,glm::vec3 b){
	glm::vec3 ab = b-a;
	float distance = sqrt(ab.x*ab.x + ab.y*ab.y + ab.z*ab.z);
	return distance;
}

//this method calculates the vertical position of the camera when
//the character is jumping
void KeyBoardEventManager::jump(Camera* camera){
	
	
	if(isJumpingUp == 1){
		dy += jumpSpeed ;
		camera->setEyeCoordinate(1 , camera->getEyeCoordinate(1)+jumpSpeed);
		camera->setObjCoordinate(1, camera->getObjectCoordinate(1)+jumpSpeed);
		
		if(dy >= jumpLimit){
			isJumpingUp = 0;
			isJumpingDown = 1;
		}
		
	}
	if(isJumpingDown == 1){
		dy -= jumpSpeed ;
		camera->setEyeCoordinate(1 , camera->getEyeCoordinate(1)-jumpSpeed);
		camera->setObjCoordinate(1, camera->getObjectCoordinate(1)-jumpSpeed);
		
		if(dy <= 0){
			isJumpingUp = 0;
			isJumpingDown = 0;
		}

	}
	
}


//this function is a trick that I have learned to implement FPS camera motion  using GLUT.
//if you pressing and holding the key the character moves without stops
void KeyBoardEventManager::eventUpKey(unsigned char keyCode,int x, int y, Car car, Camera *camera){
	
	if(keyCode == 'a' || keyCode =='A' ){ 
		move &= ~left; //bitwise operation with the mask not(left) (AND operation)
	}

	if(keyCode == 'd' || keyCode == 'D'){
		move &= ~right; //bitwise operation with the mask not(right) (AND operation)
	}

	if(keyCode == 's' || keyCode == 'S'){
		move &= ~backward; //bitwise operation with the mask not(backward) (AND operation)
	}
	if(keyCode == 'w' || keyCode == 'W'){ 
		move &= ~foward;  //bitwise operation with the mask not(foward) (AND operation)
	}
}

//this method calculate the Camera coordinates in the plane x-z when
//the keys w,a,s or/and d are pressed 
void KeyBoardEventManager::CalculateMovimentVectors(Camera* camera,float sphereAngle1,int time, glm::vec3 cubeLimitP, glm::vec3 cubeLimitN, float theshold){
	static int pt = 0;
	
 
	// Calculate time since last call to idle()
	float dt = (time - pt) * 1.0e-3;
	
	pt = time;
 
	// Calculate movement vectors
	forward_dir = glm::vec3(sin(sphereAngle1), 0, cos(sphereAngle1));
	right_dir = glm::vec3(-forward_dir.z, 0, forward_dir.x);
	
	
	
	// Update camera position
	if(move & left)
		camera->addEyeCoordinates((-right_dir * moveSpeed * dt), cubeLimitP,  cubeLimitN, theshold);
    if(move & right)
		camera->addEyeCoordinates((right_dir * moveSpeed * dt),cubeLimitP,cubeLimitN,theshold);
    if(move & foward)
		camera->addEyeCoordinates((forward_dir * moveSpeed * dt), cubeLimitP,  cubeLimitN,theshold);
    if(move & backward)
		camera->addEyeCoordinates((-forward_dir * moveSpeed * dt),cubeLimitP,  cubeLimitN,theshold);
}

//this method calculate the Car coordinates in the plane x-z when
//the keys w,a,s or/and d are pressed 
void KeyBoardEventManager::CalculateMovimentVectors(Car* car,float sphereAngle1,int time, glm::vec3 cubeLimitP, glm::vec3 cubeLimitN, float theshold){
	static int pt = 0;
	float acceleration = 3;
 
	// Calculate time since last call to idle()
	float dt = (time - pt) * 1.0e-3;
	
	pt = time;
 
	// Calculate movement vectors
	forward_dir = glm::vec3(sin(sphereAngle1), 0, cos(sphereAngle1));
	right_dir = glm::vec3(-forward_dir.z, 0, forward_dir.x);
	
	
	
	// Update camera position
	//if(move & left){
	//	car->setPosition(car->getPosition()+(-right_dir * moveSpeed * dt));
	//}
	//if(move & right){
	//	car->setPosition(car->getPosition()+(right_dir * moveSpeed * dt));
	//}
	if(move & foward){
		car->setPosition(car->getPosition()+(forward_dir * moveSpeed* acceleration * dt));
	}
	if(move & backward){
		car->setPosition(car->getPosition()+(-forward_dir * moveSpeed*acceleration* dt));
	}
	
	if(car->getPosition().x >= cubeLimitP.x-theshold){
		car->setPositionCoordinate(0, cubeLimitP.x-theshold);
	}
	
	if(car->getPosition().x <= cubeLimitN.x+theshold){
		car->setPositionCoordinate(0, cubeLimitN.x+theshold);
	}
	
	if(car->getPosition().y >= cubeLimitP.y-theshold){
		car->setPositionCoordinate(1, cubeLimitP.y-theshold);
	}
	
	if(car->getPosition().y <= cubeLimitN.y+theshold){
		car->setPositionCoordinate(1, cubeLimitN.y+theshold);
	}
	
	if(car->getPosition().z >= cubeLimitP.z-theshold){
		car->setPositionCoordinate(2, cubeLimitP.z-theshold);
	}
	
	if(car->getPosition().z <= cubeLimitN.z+theshold){
		car->setPositionCoordinate(2, cubeLimitN.z+theshold);
	}
	
}


