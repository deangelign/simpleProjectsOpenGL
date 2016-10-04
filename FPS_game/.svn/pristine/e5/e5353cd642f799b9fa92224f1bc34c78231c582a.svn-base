//include the necessary libs and class

#include <iostream>
using namespace std;
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#ifndef __APPLE__
/* Use glew.h instead of gl.h to get all the GL prototypes declared */
#include <GL/glew.h>
/* Using the GLUT library for the base windowing setup */
#include <GL/glut.h>
#else
#include<OpenGL/gl3.h>
#include<GLUT/glut.h>
#endif

#include "Camera.h"
#include "MyMesh.h"
#include "Car.h"
#include "SkyBox.h"
#include "Gun.h"
#include "MouseEventManager.h"
#include "KeyBoardEventManager.h"
#include "Spheres.h"
#include "Mirror.h"
#include "Soldier.h"
#include <cmath>


//set some global variables
int windowID;
int screen_width=800, screen_height=600;
MyMesh cube;
Car car;
MyMesh cubeGlass;
SkyBox skybox;
Mirror mirror;
Gun gun;
Soldier soldier;
Spheres spheres(1,50,50);
MouseEventManager mouse;
KeyBoardEventManager keyBoard;
Camera camera1(0.0,1.0,0.0, 0.0,1.0, 1.0, 0.0, 1.0, 0.0);
Camera camera2(0.0,30,0.0, 0.0,1.0, 0.0, 1.0, 0.0, 0.0);
Camera camera3;
Camera currentCamera;
glm::vec3 skyBoxScale = glm::vec3(100,20,100); 
glm::mat4 projection = glm::perspective(60.0f, 1.0f*screen_width/screen_height, 0.1f, 1000.0f);
int acameraIndex=0;
GLdouble eqn1[4] = { 0.0, 1.0, 0.0, 0.0 };

GLint buffers = GL_NONE;

int init_resources(){
	
	
	car.InitCarUsingGlmModel();//Store object vertices, normals and/or elements in graphic card buffers (car)
	car.setPosition(glm::vec3(0.0,0.8,3.0)); //initialize the car position
	camera3.updateCameraParameters( 0.0,2.0,0.0, 0.0,0.8,3.0, 0,1,0);//initialize the camera3 parameters
	
	
	gun.InitGunUsingGlmModel();//Store object vertices, normals and/or elements in graphic card buffers(gun)
	soldier.InitSoldierUsingGlmModel();
	soldier.setPosition(glm::vec3(0.0, 2.0 , 0.0));
	
	//Store object vertices, normals and/or elements in graphic card buffers(skybox)
	skybox.loadSkyBox("external_files/SkyBoxTextures/front.jpg",
	"external_files/SkyBoxTextures/back.jpg",
	"external_files/SkyBoxTextures/right.jpg",
	"external_files/SkyBoxTextures/left.jpg",
	"external_files/SkyBoxTextures/top.jpg");
	skybox.setPosition(glm::vec3(0.0,0.0,0.0));//initialize the skybox position.
	
	
	spheres.initSpheres("external_files/tutes/Earthmap720x360_grid.jpg", "external_files/tutes/sphere-phong.v.glsl", "shaders/fPhong.glsl");//Store object vertices, normals and/or elements in graphic card buffers(spheres)
	mirror.loadMirror("external_files/Ice/ice.jpg", "shaders/vl.glsl","shaders/fl.glsl");
	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_TEXTURE_2D);//enable textures
	glEnable(GL_LIGHTING);//enable LIGHTING
	
    
	
  return 1;
}




void onDisplay() {
	glClearColor(1.0, 1.0, 1.0, 1.0);//white backGround
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);//clear the colour, depth and Stencil buffer
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); 
	spheres.position = (glm::vec3(0.0,10.0,0.0));
	mirror.position = (glm::vec3(0.0,0.0,0.0));
	
	soldier.setPosition(glm::vec3(camera1.getEyeCoordinate(0),camera1.getEyeCoordinate(1),camera1.getEyeCoordinate(2)) );
	glm::mat4 soldierModel = glm::translate(glm::mat4(1.0f), soldier.getPosition());
	GLfloat angleSoldier = mouse.getSphereAngle(0)*(180/M_PI); 
	glm::mat4 SoldierRotation = glm::rotate(glm::mat4(1.0f), angleSoldier, glm::vec3(0, 1, 0)); 
	soldierModel = soldierModel*SoldierRotation;
	
	
	camera1.cameraMotion(mouse.getObjectCoordinatesInSphere()); //recalculating the camera1 ObjectsCoordinates based on the mouse angles 
	keyBoard.jump(&camera1);//check is the character is jumping 
	camera1.updateViewerMatrix();//update the viewrMatrix of camera1
	
	glm::mat4 modelCar = glm::translate(glm::mat4(1.0f), car.getPosition());//initializate the car model matrix
	
	
	//gun rotation (necessary to fix the gun in the first player view)
	glm::mat4 gunRotation1 =  glm::rotate(glm::mat4(1.0f), (float)270, glm::vec3(1, 0, 0));
	GLfloat angleFix1 = mouse.getSphereAngle(0)*(180/M_PI);
	glm::mat4 RotationFix1 =  glm::rotate(glm::mat4(1.0f), angleFix1, glm::vec3(0, 0, 1));
	GLfloat angleFix2 = mouse.getSphereAngle(1)*(180/M_PI);
	glm::mat4 RotationFix2 =  glm::rotate(glm::mat4(1.0f), -angleFix2, glm::vec3(1, 0, 0));
	////
	
	// set gun always at the right side of view;
	float gunX = 0.5*sin(mouse.getSphereAngle(0) - ( (M_PI/180)*30 ) )*cos(mouse.getSphereAngle(1)) + camera1.getEyeCoordinate(0);
	float gunZ = 0.5*cos(mouse.getSphereAngle(0) - ( (M_PI/180)*30 ) )*cos(mouse.getSphereAngle(1)) + camera1.getEyeCoordinate(2);
	float gunY = 0.5*sin(mouse.getSphereAngle(1)) + camera1.getEyeCoordinate(1); 
	glm::vec3 objectPositionInS = glm::vec3(gunX,gunY,gunZ);
	////
	
	
	///////// generating the final gun model matrix 
	glm::mat4 modelGun = glm::translate(glm::mat4(1.0f), objectPositionInS);
	modelGun = modelGun*gunRotation1*RotationFix1*RotationFix2;	
	////
	
	
	////checking if the player pressed the key  "e"
	if(!keyBoard.isDriving){
		
		//which camera is being used 
		if(keyBoard.cameraIndex == 0){ //normal view (first player view)
			currentCamera.recvCamera(camera1); //the current camere is camera1 (first player view)
			gun.draw(modelGun, currentCamera.getViewerMatrix(),projection, glm::vec3(1,1,1),1,glm::vec3(1,1,1)); //draw the gun
		}
		
		if(keyBoard.cameraIndex == 1){ //sky-view 
			//set the camera2 parameters based on the camera1 parameters
			camera2.setEyeCoordinate(0,  camera1.getEyeCoordinate(0));
			camera2.setEyeCoordinate(2,  camera1.getEyeCoordinate(2));
			camera2.setObjCoordinate(0,  camera1.getEyeCoordinate(0));
			camera2.setObjCoordinate(2,  camera1.getEyeCoordinate(2));
			camera2.updateViewerMatrix();
			currentCamera.recvCamera(camera2);//the current camere is camera2 (sky-view)
			soldier.draw(soldierModel, currentCamera.getViewerMatrix(),projection, glm::vec3(1,1,1),1,glm::vec3(1,1,1));
		}
	}
	
	if(keyBoard.isDriving){//if the player is driving the car
		
		modelCar = glm::translate(glm::mat4(1.0f), car.getPosition());//init the car model matrix
		//rotate the car based on the mouse
		GLfloat angleCar = mouse.getSphereAngle(0)*(180/M_PI); 
		glm::mat4 carRotation = glm::rotate(glm::mat4(1.0f), angleCar, glm::vec3(0, 1, 0)); 
		modelCar = modelCar*carRotation;
		
		////set the camera3 eye coordintes based on the car position
		////3 is the distance between the car and camera3;
		camera3.setObjCoordinates(car.getPosition());
		glm::vec3 eye3 = glm::vec3(car.getPosition().x - 3*sin(mouse.getSphereAngle(0)),camera3.getEyeCoordinate(1),car.getPosition().z-3*cos(mouse.getSphereAngle(0))  );	
		camera3.setEyeCoordinates(eye3);
		
		
		////copy the camera3 in camera1   
		camera1.recvCamera(camera3);
		camera1.setEyeCoordinate(1,1.0);//camera1 height correction
		
		
		
		//which camera is being used 
		if(keyBoard.cameraIndex == 0){//car camera
			currentCamera.recvCamera(camera3);//the current camere is camera3 (car camera)
		}
		
		if(keyBoard.cameraIndex == 1){//sky-view
			//set the camera2 parameters based on the camera3 parameters
			camera2.setEyeCoordinate(0,  camera3.getEyeCoordinate(0));
			camera2.setEyeCoordinate(2,  camera3.getEyeCoordinate(2));
			camera2.setObjCoordinate(0,  camera3.getEyeCoordinate(0));
			camera2.setObjCoordinate(2,  camera3.getEyeCoordinate(2));
			camera2.updateViewerMatrix();
			currentCamera.recvCamera(camera2);//the current camere is camera2 (sky-view)
			
		}
	}

	//draw the skybox
	skybox.draw(currentCamera.getViewerMatrix(),projection,skyBoxScale, keyBoard.cameraIndex);
	spheres.draw(currentCamera.getViewerMatrix(),projection,glm::vec3(1,1,1), glm::vec3(1,1,1));
	car.draw(modelCar, currentCamera.getViewerMatrix(),projection, glm::vec3(1,1,1),1.0, glm::vec3(1,1,1));
	
	
	//drawing the objects in the mirror
	//reflection 
	glEnable(GL_STENCIL_TEST);
	
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilMask(0xFF);
	glDepthMask(GL_FALSE);

    glClear(GL_STENCIL_BUFFER_BIT);
	mirror.draw(currentCamera.getViewerMatrix(),projection,glm::vec3(100,20,100),0.8,glm::vec3(1,1,1));
	
	glStencilFunc(GL_EQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glDepthMask(GL_TRUE);
	spheres.position = (glm::vec3(0.0,-10.0,0.0));
	spheres.draw(currentCamera.getViewerMatrix(),projection,glm::vec3(1,-1,1), glm::vec3(0.5,0.5,0.5));
	modelCar[3][1] = -modelCar[3][1];
	car.draw(modelCar, currentCamera.getViewerMatrix(),projection, glm::vec3(1,-1,1),0.9, glm::vec3(0.5,0.5,0.5));
	if(!keyBoard.isDriving){
		soldierModel[3][1] = -soldierModel[3][1];
		soldier.draw(soldierModel, currentCamera.getViewerMatrix(),projection, glm::vec3(1,-1,1),0.9,glm::vec3(0.5,0.5,0.5));
	}
	
	glDisable(GL_STENCIL_TEST);
	
	glutSwapBuffers();

  
}

void idle() {
  
	// time since last call to idle()
	int t = glutGet(GLUT_ELAPSED_TIME);
  

	// Calculate movement vectors
	if(keyBoard.isDriving){
		keyBoard.CalculateMovimentVectors(&car, mouse.getSphereAngle(0),t , glm::vec3(100,20,100),glm::vec3(-100,0,-100),1 );
		camera3.setObjCoordinates(car.getPosition());
	}else{
		keyBoard.CalculateMovimentVectors(&camera1, mouse.getSphereAngle(0),t , glm::vec3(100,20,100),glm::vec3(-100,0,-100),1 );
	}
	
	if(!keyBoard.isEscape){
		glutPostRedisplay();
	}else{
		void glutLeaveMainLoop ( void );
		glutDestroyWindow ( windowID );
		exit(0);
	}
}

void onReshape(int width, int height) {
  screen_width = width;
  screen_height = height;
  glViewport(0, 0, screen_width, screen_height);
}

//send the keyboard events to a instance of KeyBoardEventManager
void keyboard_handler(unsigned  char key, int x, int y){
	keyBoard.eventKey(key, x,  y, car,&currentCamera, &mouse);
}

void keyboard_handlerUP(unsigned  char key, int x, int y){
	keyBoard.eventUpKey(key, x,  y, car,&currentCamera);
}

//send the mouse events to a instace of MouseEventManager
void motion(int x, int y) {
	mouse.motion(x,y,screen_width,screen_height);
	
}


 
int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
#ifdef MACOSX
//  glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA|GLUT_ALPHA|GLUT_DOUBLE|GLUT_DEPTH);
  glutInitDisplayMode(GLUT_RGBA|GLUT_ALPHA|GLUT_DOUBLE|GLUT_DEPTH);
#else
  glutInitDisplayMode( GLUT_RGBA|GLUT_ALPHA|GLUT_DOUBLE|GLUT_DEPTH);
#endif
  glutInitWindowSize(screen_width, screen_height);
  windowID = glutCreateWindow("FPS game");

GLenum glew_status = glewInit();

#ifndef MACOSX
  if (glew_status != GLEW_OK) {
    fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
    return EXIT_FAILURE;
  }

  if (!GLEW_VERSION_2_0) {
    fprintf(stderr, "Error: your graphic card does not support OpenGL 2.0\n");
    return EXIT_FAILURE;
  }
#endif

  if (init_resources()) {
    glutDisplayFunc(onDisplay);
    glutReshapeFunc(onReshape);
    glutKeyboardFunc(keyboard_handler);
    glutKeyboardUpFunc(keyboard_handlerUP);
	glutPassiveMotionFunc(motion);
	glutIdleFunc(idle);
	glutSetCursor(GLUT_CURSOR_NONE);//hide the mouse cursor
    glEnable(GL_DEPTH_TEST);
	
	
    glAlphaFunc(GL_GREATER, 0.1);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);//enable transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    glutMainLoop();
    cout << "kk" << endl;
  }

  //free_resources();
  return EXIT_SUCCESS;
}

