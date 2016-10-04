//code written by Deangeli Gomes Neves

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "MyMesh.h"
//#include <GL/glut.h>
//#include "external_files/glm/glm.hpp"
//#include "external_files/glm/gtc/matrix_transform.hpp"
//#include "external_files/glm/gtc/type_ptr.hpp"
//#include "external_files/glm/matrix.hpp"
//#include "external_files/glm/matrix.hpp"

class Camera{
private:
	GLfloat eyeCoordinates[3];
	GLfloat objectCoordinates[3]; 
	GLint upVectors[3];
	glm::mat4 viewerMatrix;

public:
	
	Camera();
	Camera(GLfloat eye_X, GLfloat eye_Y, GLfloat eye_Z, GLfloat obj_X, GLfloat obj_Y, GLfloat obj_Z, GLint up_X, GLint up_Y, GLint up_Z);
	
	void setEyeCoordinates(GLfloat eye_X, GLfloat eye_Y, GLfloat eye_Z);
	void setEyeCoordinates(glm::vec3 _eyeCoordinates);
	void setObjCoordinates(glm::vec3 _objCoordinates);
	void setEyeCoordinate(int index,  GLfloat eye_coord);
	void setObjCoordinate(int index,  GLfloat obj_coord);
	
	void setObjectCoordinates(GLfloat obj_X, GLfloat obj_Y, GLfloat obj_Z);
	void setUpVectors(GLint up_X, GLint up_Y, GLint up_Z);
	void updateCameraParameters(GLfloat eye_X, GLfloat eye_Y, GLfloat eye_Z, GLfloat obj_X, GLfloat obj_Y, GLfloat obj_Z,GLint up_X,GLint up_Y,GLint up_Z);
	void updateViewerMatrix();
	
	void addEyeCoordinates(glm::vec3 _eyeCoordinates,glm::vec3 cubeLimitP,glm::vec3 cubeLimitN, float theshold);
	
	
	
	glm::mat4 getViewerMatrix();
	GLfloat* getEyeCoordinates();
	GLfloat* getObjectCoordinates();
	GLint* getUpVectors();
	
	GLfloat getEyeCoordinate(int index);
	GLfloat getObjectCoordinate(int index);
	GLint getUpVector(int index);
	
	void cameraMotion(glm::vec3 objectCoordinatesInSphere);
	void cameraMotionCar(glm::vec3 objectCoordinatesInSphere,float radius, float theshold, glm::vec3 limitsP, glm::vec3 limitsN);
	void cameraPrint();
	void recvCamera(Camera camera);
	
};

#endif
