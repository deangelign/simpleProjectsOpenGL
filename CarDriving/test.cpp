//fourth pass - use SOIL to read in texture files, add buffers for texture cords etc
#include <iostream>
#include<stack>
using namespace std;
#include <stdlib.h>
#include <math.h>
#ifndef __APPLE__
/* Use glew.h instead of gl.h to get all the GL prototypes declared */
#include <GL/glew.h>
/* Using the GLUT library for the base windowing setup */
#include <GL/glut.h>
#else
#include<OpenGL/gl3.h>
#include<GLUT/glut.h>
#endif
/* Nate Robbins glm */
#include "glm_mod.h"
/* GLM */
// #define GLM_MESSAGES
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/matrix.hpp"
#include "SOIL/SOIL.h"
#include "InitShader.cpp"
#include "ground.c"
#include "track.c"
#include "forest.c"
#include "sky.c"
//#include "wheel.c"

GLuint screen_width=800, screen_height=600;
GLfloat groundScale = 20;

//track - ellipses

//internal ellipse
float r_in_x = 6;
float r_in_y = 8;
//external ellipse	
float r_out_x = 8;
float r_out_y = 10;

//car position
GLfloat CarX = 7.0f;
GLfloat CarY = 0.6f;
GLfloat CarZ = 0.0f;
GLfloat angle = 0.0;
GLfloat rx_elipse_car = (r_in_x + r_out_x)/2.;
GLfloat ry_elipse_car = (r_in_y + r_out_y)/2.;
GLfloat step = M_PI /180.0;
GLint iter = 0;


//projection
glm::mat4 projection = glm::perspective(70.0f, 1.0f*screen_width/screen_height, 0.1f, 100.0f);
////

//camera1 -outside
//GLfloat eye1_x = 7.0f;
//GLfloat eye1_y = 10.0f;
//GLfloat eye1_z = -5.0f;

//GLfloat obj1_x = CarX;
//GLfloat obj1_y = CarY;
//GLfloat obj1_z = CarZ;

GLfloat eye1_x = 0.0f;
GLfloat eye1_y = 10.0f;
GLfloat eye1_z = 0.0f;

GLfloat obj1_x = 0;
GLfloat obj1_y = 20;
GLfloat obj1_z = 0;



GLint upx1 = 1;
GLint upy1 = 0;
GLint upz1 = 0;
glm::mat4 camera1 = glm::lookAt(glm::vec3(eye1_x, eye1_y , eye1_z), glm::vec3(obj1_x, obj1_y, obj1_z), glm::vec3(upx1, upy1, upz1));
//////////////

//camera2 -outside
GLfloat eye2_x = CarX;
GLfloat eye2_y = CarY;
GLfloat eye2_z = CarZ+0.5;

GLfloat obj2_x = rx_elipse_car * cos(step * (iter+10));
GLfloat obj2_y = CarY;
GLfloat obj2_z = ry_elipse_car * sin(step * (iter+10));

GLint upx2 = 0;
GLint upy2 = 1;
GLint upz2 = 0;
glm::mat4 camera2 = glm::lookAt(glm::vec3(eye2_x, eye2_y , eye2_z), glm::vec3(obj2_x, obj2_y, obj2_z), glm::vec3(upx2, upy2, upz2));
//////////////

glm::mat4 model_sky = glm::mat4(1.0f);
glm::mat4 mv_sky = glm::mat4(1.0f);
glm::mat4 mv_sky2 = glm::mat4(1.0f);


//sky
GLint attibuteID_sky[3]; // 0 - vertices 1 - texcoords 2 - normals ;
GLint uniformMatrixID_sky[3]; //0 - mv 1 - projection 2 -  mytexture;
glm::vec3 skyVertices[4];
glm::vec3 skyNormals[4];
glm::vec2 sky_texcoords[4];

GLuint skyBuffersID[3];//0 - vertices 1 - texCoords 2 - NormalsGLuint textureID_forest;
GLuint textureID_sky;


//0 - car
//1 = ground
//2 = track
//3 = house
//4 = forest
//5 = sky
GLuint vao[6];

//1 = ground
//2 = track
//3 = forest
//4 = sky
GLuint programID1,programID2,programID3, programID4;




void generateSky(){
	//front
	skyVertices[0] = glm::vec3(-1.0f, 1.0f,  1.0f); sky_texcoords[0] = glm::vec2(0.0f , 0.0f); 
	skyVertices[1] = glm::vec3(1.0f, 1.0f,  1.0f);  sky_texcoords[1] = glm::vec2(1.0f , 0.0f);
	skyVertices[2] = glm::vec3(1.0f, 1.0f,  -1.0f);  sky_texcoords[2] = glm::vec2(1.0f , 1.0f);
	skyVertices[3] = glm::vec3(-1.0f, 1.0f,  -1.0f); sky_texcoords[3] = glm::vec2(0.0f , 1.0f);
	
	skyNormals[0] = skyNormals[1] = skyNormals[2] = skyNormals[3] = glm::vec3(0.0,1.0,0.0);
	
}

void getAttiributeAndUniformIDSky(){
	const char* attribute_name;
	attribute_name = "coord3d";
	attibuteID_sky[0] = glGetAttribLocation(programID4, attribute_name);
	if (attibuteID_sky[0] == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
		
	}
	
	attribute_name = "texcoord";
	attibuteID_sky[1] = glGetAttribLocation(programID4, attribute_name);
	if (attibuteID_sky[1] == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
	}
	
	const char* uniform_name;
	uniform_name = "mv";
	uniformMatrixID_sky[0] = glGetUniformLocation(programID4, uniform_name);
	if (uniformMatrixID_sky[0] == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
	}
	
	
	uniform_name = "projection";
	uniformMatrixID_sky[1] = glGetUniformLocation(programID4, uniform_name);
	if (uniformMatrixID_sky[1] == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
	}
	
	uniform_name = "mytexture";
	uniformMatrixID_sky[2] = glGetUniformLocation(programID4, uniform_name);
	if (uniformMatrixID_sky[2] == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
	}

}

void initSky(){
	generateSky();
	getAttiributeAndUniformIDSky();
	//
	glGenBuffers(3, skyBuffersID);
	glBindBuffer( GL_ARRAY_BUFFER, skyBuffersID[0] );
	glBufferData( GL_ARRAY_BUFFER, sizeof(skyVertices), skyVertices, GL_STATIC_DRAW );
	
	glBindBuffer( GL_ARRAY_BUFFER, skyBuffersID[1] );
	glBufferData( GL_ARRAY_BUFFER, sizeof(sky_texcoords), sky_texcoords, GL_STATIC_DRAW );
	
	glBindBuffer( GL_ARRAY_BUFFER, skyBuffersID[2] );
	glBufferData( GL_ARRAY_BUFFER, sizeof(skyNormals), skyNormals, GL_STATIC_DRAW );
	
	glGenTextures(1, &textureID_sky);
	glBindTexture(GL_TEXTURE_2D, textureID_sky);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sky.width, sky.height, 0, GL_RGB,  GL_UNSIGNED_BYTE, sky.pixel_data);
	
	//which data are we going to use for positions
	glBindBuffer(GL_ARRAY_BUFFER, skyBuffersID[0]);
	glEnableVertexAttribArray(attibuteID_sky[0]);
	// Describe our vertices array to OpenGL (it can't guess its format automatically)
	glVertexAttribPointer(attibuteID_sky[0], 3, GL_FLOAT, GL_FALSE, 0, 0 );
	
	//which data are we going to use for texccords
	glBindBuffer(GL_ARRAY_BUFFER, skyBuffersID[1]);
	glEnableVertexAttribArray(attibuteID_sky[1]);
	glVertexAttribPointer(attibuteID_sky[1], 2, GL_FLOAT, GL_FALSE,0,0);
}

void drawSky(){
	glUseProgram(programID4);
	glBindVertexArray(vao[5]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID_sky);
	glUniform1i(uniformMatrixID_sky[2], /*GL_TEXTURE*/0);

	glDrawArrays(GL_QUADS, 0, 4);
}


void init(){
	
	glGenVertexArrays( 6, vao );
		
	glBindVertexArray(vao[5]);
	programID4 = InitShader("vSky.glsl","fSky.glsl");
	glUseProgram(programID4);
	initSky();
}

void onIdle() {
	CarX = rx_elipse_car * cos(step * iter);
	CarZ = ry_elipse_car * sin(step * iter);
	angle = -step * iter * (180/M_PI);
  
	//obj1_x = rx_elipse_car * cos(step * (iter+5));
	//obj1_z = ry_elipse_car * sin(step * (iter+5));
	
	obj1_x = 20 * cos(step * iter);
	obj1_z = 20 * sin(step * iter);
	
	//eye1_x =  rx_elipse_car * cos(step * (iter-20));
	//eye1_z =  ry_elipse_car * sin(step * (iter-20));
	
	camera1 = glm::lookAt(glm::vec3(eye1_x, eye1_y , eye1_z), glm::vec3(obj1_x, obj1_y, obj1_z), glm::vec3(upx1, upy1, upz1));
  
	GLfloat eye2_x = CarX;
	GLfloat eye2_y = CarY;
	GLfloat eye2_z = CarZ+0.5;

	GLfloat obj2_x = rx_elipse_car * cos(step * (iter+10));
	GLfloat obj2_y = CarY;
	GLfloat obj2_z = ry_elipse_car * sin(step * (iter+10));
  
	camera2 = glm::lookAt(glm::vec3(eye2_x, eye2_y , eye2_z), glm::vec3(obj2_x, obj2_y, obj2_z), glm::vec3(upx2, upy2, upz2));
  
	iter++;
	if(iter >= 360){
		iter = 0;
	}
	glutPostRedisplay();
}

void onDisplay()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );


	glm::vec3 axis_y(0, 1, 0);
	glm::mat4 anim = glm::rotate(glm::mat4(1.0f), angle, axis_y);

  
	
	
	
	
	model_sky = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));	
	mv_sky = camera1 * model_sky ;// this is the overall transorm of our composited model - rotate it, translate it away from origin. Then position our viewer and set the projection.
	mv_sky = glm::scale(mv_sky,glm::vec3(groundScale,groundScale,groundScale)); 
	
  
  
	
	
	glBindVertexArray(vao[5]);
	glUseProgram(programID4);
	glBindBuffer(GL_ARRAY_BUFFER, skyBuffersID[0]);
   
	glUniformMatrix4fv(uniformMatrixID_sky[0], 1, GL_FALSE, glm::value_ptr(mv_sky));
	glUniformMatrix4fv(uniformMatrixID_sky[1], 1, GL_FALSE, glm::value_ptr(projection));
   
	drawSky();

	
	
	
	glutSwapBuffers();
}



void onReshape(int width, int height) {
  screen_width = width;
  screen_height = height;
  glViewport(0, 0, screen_width, screen_height);
}



int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  //glutInitDisplayMode(GLUT_RGBA|GLUT_ALPHA|GLUT_DOUBLE|GLUT_DEPTH);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
  glutInitWindowSize(screen_width, screen_height);
  glutCreateWindow("My Object");

#ifndef __APPLE__
  GLenum glew_status = glewInit();
  if (glew_status != GLEW_OK) {
    cerr << "Error: " <<  glewGetErrorString(glew_status) << endl;
    return 1;
  }

  if (!GLEW_VERSION_2_0) {
    cerr <<  "Error: your graphic card does not support OpenGL 2.0\n" << endl;
    return 1;
  }
#endif

	init();
    glutDisplayFunc(onDisplay);
    glutReshapeFunc(onReshape);
    glutIdleFunc(onIdle);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
  

  
  return 0;
}
