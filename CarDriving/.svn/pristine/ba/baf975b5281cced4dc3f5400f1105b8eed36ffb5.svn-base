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

//textures
#include "ground.c"
#include "forest.c"
#include "sky.c"
#include "track.c"

#include "car_interior.c"


//window size
GLuint screen_width=800, screen_height=600;

//internal ellipse
float r_in_x = 6;
float r_in_y = 8;
//external ellipse	
float r_out_x = 8;
float r_out_y = 10;

//variables used to calculate the car position
GLfloat CarX = 7.0f;
GLfloat CarY = 0.6f;
GLfloat CarZ = 0.0f;
GLfloat angle = 0.0;
GLfloat rx_elipse_car = (r_in_x + r_out_x)/2.;
GLfloat ry_elipse_car = (r_in_y + r_out_y)/2.;
GLfloat step = M_PI /180.0;
GLint iter = 0;


//projection matrix
glm::mat4 projection = glm::perspective(60.0f, 1.0f*screen_width/screen_height, 0.1f, 100.0f);
////

GLint camera1Position=0;
//camera1 outside (sky view)

//GLfloat eye1_x = 7.0f;
//GLfloat eye1_y = 10.0f;
//GLfloat eye1_z = -5.0f;

//GLfloat obj1_x = CarX;
//GLfloat obj1_y = CarY;
//GLfloat obj1_z = CarZ;

GLfloat eye1_x = 0.0f;
GLfloat eye1_y = 20.0f;
GLfloat eye1_z = 0.0f;

GLfloat obj1_x = 0;
GLfloat obj1_y = 0;
GLfloat obj1_z = 0;

GLint upx1 = 1;
GLint upy1 = 0;
GLint upz1 = 0;
glm::mat4 camera1 = glm::lookAt(glm::vec3(eye1_x, eye1_y , eye1_z), glm::vec3(obj1_x, obj1_y, obj1_z), glm::vec3(upx1, upy1, upz1));
//////////////

//camera2 inside
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

//camera3 inside steering wheel

GLfloat eye3_x = 0.0;
GLfloat eye3_y = 0.0;
GLfloat eye3_z = 1.2;

GLfloat obj3_x = 0.0;
GLfloat obj3_y = 0.0;
GLfloat obj3_z = 0.0;

GLint upx3 = 0;
GLint upy3 = 1;
GLint upz3 = 0;
glm::mat4 camera3 = glm::lookAt(glm::vec3(eye3_x, eye3_y , eye3_z), glm::vec3(obj3_x, obj3_y, obj3_z), glm::vec3(upx3, upy3, upz3));
//////////////

//objects matrices 
//ground matrices: model, model-view(camera1), model-view(camera2)
glm::mat4 model_ground = glm::mat4(1.0f);
glm::mat4 mv_ground = glm::mat4(1.0f);
glm::mat4 mv_ground2 = glm::mat4(1.0f);

//forest matrices: model, model-view(camera1), model-view(camera2)
glm::mat4 model_forest = glm::mat4(1.0f);
glm::mat4 mv_forest = glm::mat4(1.0f);
glm::mat4 mv_forest2 = glm::mat4(1.0f);

//steering wheel matrices: model, model-view(camera3)
glm::mat4 model_Interior = glm::mat4(1.0f);
glm::mat4 mv_Interior = glm::mat4(1.0f);

//sky matrices: model, model-view(camera1), model-view(camera2)
glm::mat4 model_sky = glm::mat4(1.0f);
glm::mat4 mv_sky = glm::mat4(1.0f);
glm::mat4 mv_sky2 = glm::mat4(1.0f);

//car matrices: model, model-view(camera1), model-view(camera2)
glm::mat4 model_car = glm::mat4(1.0f);
glm::mat4 mv_car = glm::mat4(1.0f);
glm::mat4 mv_car2 = glm::mat4(1.0f);

//track matrices: model, model-view(camera1), model-view(camera2)
glm::mat4 model_track = glm::mat4(1.0f);
glm::mat4 mv_track = glm::mat4(1.0f);
glm::mat4 mv_track2 = glm::mat4(1.0f);

//house matrices: model, model-view(camera1), model-view(camera2)
glm::mat4 MatrixModelHouse = glm::mat4(1.0f);
glm::mat4 mv_house = glm::mat4(1.0f);
glm::mat4 mv_house2 = glm::mat4(1.0f);


//Ground 
GLint attibuteID_ground[3]; //attribute IDs 0 - vertices 1 - texcoords 2 - normals ;
GLint uniformMatrixID_ground[3];//uniforms IDs 0 - mv 1 - projection 2 -  mytexture;
glm::vec3 groundVertices[4]; 
glm::vec3 groundNormals[4];
glm::vec2 ground_texcoords[4];
GLuint groundBuffersID[3];//ground Buffers Id 0 - vertices 1 - texCoords 2 - Normals
GLuint textureID_ground;
GLfloat groundScale = 20; //Used to rize the "skybox"

//track
GLint attibuteID_track[3]; // 0 - vertices 1 - texcoords 2 - normals ;
GLint uniformMatrixID_track[3]; //0 - mv 1 - projection 2 -  mytexture;
glm::vec3 trackVertices[1440]; //store the vertices of ellipses
glm::vec3 trackNormals[1440];
glm::vec2 track_texcoords[1440];
GLuint trackBuffersID[3];//0 - vertices 1 - texCoords 2 - Normals
GLuint textureID_track;

//forest
GLint attibuteID_forest[3]; // 0 - vertices 1 - texcoords 2 - normals ;
GLint uniformMatrixID_forest[3]; //0 - mv 1 - projection 2 -  mytexture;
glm::vec3 forestVertices[16];
glm::vec3 forestNormals[16];
glm::vec2 forest_texcoords[16];
GLuint forestBuffersID[3];//0 - vertices 1 - texCoords 2 - Normals
GLuint textureID_forest;

//sky
GLint attibuteID_sky[3]; // 0 - vertices 1 - texcoords 2 - normals ;
GLint uniformMatrixID_sky[3]; //0 - mv 1 - projection 2 -  mytexture;
glm::vec3 skyVertices[4];
glm::vec3 skyNormals[4];
glm::vec2 sky_texcoords[4];
GLuint skyBuffersID[3];//0 - vertices 1 - texCoords 2 - NormalsGLuint textureID_forest;
GLuint textureID_sky;


//car_interior = car_interior (steering wheel + ...)
GLint attibuteID_interior[3]; // 0 - vertices 1 - texcoords 2 - normals ;
GLint uniformMatrixID_interior[3]; //0 - mv 1 - projection 2 -  mytexture;
glm::vec3 interiorVertices[4];
glm::vec2 interior_texcoords[4];

GLuint interiorBuffersID[2];//0 - vertices 1 - texCoords 
GLuint textureID_interior;

//0 - car
//1 = ground
//2 = track
//3 = house
//4 = forest
//5 = sky
GLuint vao[7];

//1 = ground
//2 = track
//3 = forest
//4 = sky
GLuint programID1,programID2,programID3, programID4, programID5;


GLMmodel* model_ptr = NULL;//car
GLMmodel* model_house = NULL;//house

//I have written several fuctions because is easier (for me) debbuging my own code
//I have used a lot buffers because is easier (for me) debbuging my own code

//generate steering wheel points (square)
void generateInterior(){
	interiorVertices[0] = glm::vec3(-1.0,-1.0,0.0); interior_texcoords[0] = glm::vec2(0.0f , 0.0f); 
	interiorVertices[1] = glm::vec3(1.0,-1.0,0.0);  interior_texcoords[1] = glm::vec2(1.0f , 0.0f); 
	interiorVertices[2] = glm::vec3(1.0,1.0,0.0);	interior_texcoords[2] = glm::vec2(1.0f , 1.0f); 
	interiorVertices[3] = glm::vec3(-1.0,1.0,0.0);	interior_texcoords[3] = glm::vec2(0.0f , 1.0f); 
}

//generate steering wheel points (square)
void generateSky(){
	//top of the skybox
	skyVertices[0] = glm::vec3(-1.0f, 1.0f,  1.0f); sky_texcoords[0] = glm::vec2(0.0f , 0.0f); 
	skyVertices[1] = glm::vec3(1.0f, 1.0f,  1.0f);  sky_texcoords[1] = glm::vec2(1.0f , 0.0f);
	skyVertices[2] = glm::vec3(1.0f, 1.0f,  -1.0f);  sky_texcoords[2] = glm::vec2(1.0f , 1.0f);
	skyVertices[3] = glm::vec3(-1.0f, 1.0f,  -1.0f); sky_texcoords[3] = glm::vec2(0.0f , 1.0f);
	
	skyNormals[0] = skyNormals[1] = skyNormals[2] = skyNormals[3] = glm::vec3(0.0,1.0,0.0);
	
}

void generateForest(){
	//front of the skybox
	forestVertices[0] = glm::vec3(-1.0f, 0.0f,  1.0f); forest_texcoords[0] = glm::vec2(0.0f , 0.0f); 
	forestVertices[1] = glm::vec3(1.0f, 0.0f,  1.0f);  forest_texcoords[1] = glm::vec2(1.0f , 0.0f);
	forestVertices[2] = glm::vec3(1.0f, 1.0f,  1.0f);  forest_texcoords[2] = glm::vec2(1.0f , 1.0f);
	forestVertices[3] = glm::vec3(-1.0f, 1.0f,  1.0f); forest_texcoords[3] = glm::vec2(0.0f , 1.0f);
	
	forestNormals[0] = forestNormals[1] = forestNormals[2] = forestNormals[3] = glm::vec3(0.0,0.0,1.0);
	
	//left of the skybox
	forestVertices[4] = glm::vec3(-1.0f, 0.0f,  1.0f); forest_texcoords[4] = glm::vec2(0.0f , 0.0f); 
	forestVertices[5] = glm::vec3(-1.0f, 0.0f,  -1.0f);  forest_texcoords[5] = glm::vec2(1.0f , 0.0f);
	forestVertices[6] = glm::vec3(-1.0f, 1.0f,  -1.0f);  forest_texcoords[6] = glm::vec2(1.0f , 1.0f);
	forestVertices[7] = glm::vec3(-1.0f, 1.0f,  1.0f); forest_texcoords[7] = glm::vec2(0.0f , 1.0f); 
	
	forestNormals[4] = forestNormals[5] = forestNormals[6] = forestNormals[7] = glm::vec3(-1.0,0.0,0.0);
	
	//right of the skybox
	forestVertices[8] = glm::vec3(1.0f, 0.0f,  1.0f); forest_texcoords[8] = glm::vec2(0.0f , 0.0f); 
	forestVertices[9] = glm::vec3(1.0f, 0.0f,  -1.0f);  forest_texcoords[9] = glm::vec2(1.0f , 0.0f);
	forestVertices[10] = glm::vec3(1.0f, 1.0f,  -1.0f);  forest_texcoords[10] = glm::vec2(1.0f , 1.0f);
	forestVertices[11] = glm::vec3(1.0f, 1.0f,  1.0f); forest_texcoords[11] = glm::vec2(0.0f , 1.0f);
	
	forestNormals[8] = forestNormals[9] = forestNormals[10] = forestNormals[11] = glm::vec3(1.0,0.0,0.0);
	
	//back of the skybox
	forestVertices[12] = glm::vec3(1.0f, 0.0f,  -1.0f); forest_texcoords[12] = glm::vec2(0.0f , 0.0f); 
	forestVertices[13] = glm::vec3(1.0f, 1.0f,  -1.0f);  forest_texcoords[13] = glm::vec2(0.0f , 1.0f);
	forestVertices[14] = glm::vec3(-1.0f, 1.0f,  -1.0f);  forest_texcoords[14] = glm::vec2(1.0f , 1.0f);
	forestVertices[15] = glm::vec3(-1.0f, 0.0f,  -1.0f); forest_texcoords[15] = glm::vec2(1.0f , 0.0f);
	
	forestNormals[12] = forestNormals[13] = forestNormals[14] = forestNormals[15] = glm::vec3(0.0,0.0,-1.0);
	
}


void generateTrack(){
	float deltaTheta = M_PI /180.0 ;//1 degree - x deltaTheta
	
	
	int k=0;
	
	for(int i=0;i< 360; i++ ){
		//getting the points of internal ellipse
		trackVertices[k] = glm::vec3(r_in_x * cos(deltaTheta*i), 0.0, r_in_y * sin(deltaTheta*i)); 
		track_texcoords[k] = glm::vec2(0.0f , 0.0f); 
		k++;
		
		//getting the points of external ellipse
		trackVertices[k] = glm::vec3(r_out_x * cos(deltaTheta*i), 0.0, r_out_y * sin(deltaTheta*i));
		track_texcoords[k] = glm::vec2(1.0f , 0.0f);
		k++;
		
		//getting the points of external ellipse
		trackVertices[k] = glm::vec3(r_out_x * cos(deltaTheta*(i+1)), 0.0, r_out_y * sin(deltaTheta*(i+1)));
		track_texcoords[k] = glm::vec2(1.0f , 1.0f);
		k++;
		
		//getting the points of internal ellipse
		trackVertices[k] = glm::vec3(r_in_x * cos(deltaTheta*(i+1)), 0.0, r_in_y * sin(deltaTheta*(i+1)));
		track_texcoords[k] = glm::vec2(0.0f , 1.0f);
		k++;
	}
	
	
}

void generateGround(){
	
	//vertices and texcoords 
	// bottom of the skybox
	groundVertices[0] = glm::vec3(-1.0f, 0.0f,  1.0f); ground_texcoords[0] = glm::vec2(0.0f , 0.0f); 
	groundVertices[1] = glm::vec3(1.0f, 0.0f,  1.0f);  ground_texcoords[1] = glm::vec2(1.0f , 0.0f);
	groundVertices[2] = glm::vec3(1.0f, 0.0f,  -1.0f); ground_texcoords[2] = glm::vec2(1.0f , 1.0f);
	groundVertices[3] = glm::vec3(-1.0f, 0.0f,  -1.0f); ground_texcoords[3] = glm::vec2(0.0f , 1.0f);
	
	//normals
	groundNormals[0] = glm::vec3(0.0f, 1.0f,  0.0f);
	groundNormals[1] = glm::vec3(0.0f, 1.0f,  0.0f);
	groundNormals[2] = glm::vec3(0.0f, 1.0f,  0.0f);
	groundNormals[3] = glm::vec3(0.0f, 1.0f,  0.0f);


}

//I have encapsulated the process of obtation of the attributes and uniforms names

//obtation of the attributes and uniforms of track
void getAttiributeAndUniformIDTrack(){
	const char* attribute_name;
	attribute_name = "coord3d";
	attibuteID_track[0] = glGetAttribLocation(programID2, attribute_name);
	if (attibuteID_track[0] == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
		
	}
	
	attribute_name = "texcoord";
	attibuteID_track[1] = glGetAttribLocation(programID2, attribute_name);
	if (attibuteID_track[1] == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
	}
	
	const char* uniform_name;
	uniform_name = "mv";
	uniformMatrixID_track[0] = glGetUniformLocation(programID2, uniform_name);
	if (uniformMatrixID_track[0] == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
	}
	
	
	uniform_name = "projection";
	uniformMatrixID_track[1] = glGetUniformLocation(programID2, uniform_name);
	if (uniformMatrixID_track[1] == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
	}
	
	uniform_name = "mytexture";
	uniformMatrixID_track[2] = glGetUniformLocation(programID2, uniform_name);
	if (uniformMatrixID_track[2] == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
	}

}

//obtation of the attributes and uniforms of Ground
void getAttiributeAndUniformIDGround(){
	const char* attribute_name;
	attribute_name = "coord3d";
	attibuteID_ground[0] = glGetAttribLocation(programID1, attribute_name);
	if (attibuteID_ground[0] == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
		
	}
	
	attribute_name = "texcoord";
	attibuteID_ground[1] = glGetAttribLocation(programID1, attribute_name);
	if (attibuteID_ground[1] == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
	}
	
	const char* uniform_name;
	uniform_name = "mv";
	uniformMatrixID_ground[0] = glGetUniformLocation(programID1, uniform_name);
	if (uniformMatrixID_ground[0] == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
	}
	
	
	uniform_name = "projection";
	uniformMatrixID_ground[1] = glGetUniformLocation(programID1, uniform_name);
	if (uniformMatrixID_ground[1] == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
	}
	
	uniform_name = "mytexture";
	uniformMatrixID_ground[2] = glGetUniformLocation(programID1, uniform_name);
	if (uniformMatrixID_ground[2] == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
	}

}

//obtation of the attributes and uniforms of Forest
void getAttiributeAndUniformIDForest(){
	const char* attribute_name;
	attribute_name = "coord3d";
	attibuteID_forest[0] = glGetAttribLocation(programID3, attribute_name);
	if (attibuteID_forest[0] == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
		
	}
	
	attribute_name = "texcoord";
	attibuteID_forest[1] = glGetAttribLocation(programID3, attribute_name);
	if (attibuteID_forest[1] == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
	}
	
	const char* uniform_name;
	uniform_name = "mv";
	uniformMatrixID_forest[0] = glGetUniformLocation(programID3, uniform_name);
	if (uniformMatrixID_forest[0] == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
	}
	
	
	uniform_name = "projection";
	uniformMatrixID_forest[1] = glGetUniformLocation(programID3, uniform_name);
	if (uniformMatrixID_forest[1] == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
	}
	
	uniform_name = "mytexture";
	uniformMatrixID_forest[2] = glGetUniformLocation(programID3, uniform_name);
	if (uniformMatrixID_forest[2] == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
	}

}

//obtation of the attributes and uniforms of Sky
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

//obtation of the attributes and uniforms of wheel
void getAttiributeAndUniformIDInterior(){
	const char* attribute_name;
	attribute_name = "coord3d";
	attibuteID_interior[0] = glGetAttribLocation(programID5, attribute_name);
	if (attibuteID_interior[0] == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
		
	}
	
	attribute_name = "texcoord";
	attibuteID_interior[1] = glGetAttribLocation(programID5, attribute_name);
	if (attibuteID_interior[1] == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
	}
	
	const char* uniform_name;
	uniform_name = "mv";
	uniformMatrixID_interior[0] = glGetUniformLocation(programID5, uniform_name);
	if (uniformMatrixID_interior[0] == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
	}
	
	uniform_name = "projection";
	uniformMatrixID_interior[1] = glGetUniformLocation(programID5, uniform_name);
	if (uniformMatrixID_interior[1] == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
	}
	
	uniform_name = "mytexture";
	uniformMatrixID_interior[2] = glGetUniformLocation(programID5, uniform_name);
	if (uniformMatrixID_interior[2] == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
	}

}

//generate the track vertices
//obtain the attributes and uniforms names
//create the track VBOs, store the data within it
//linkt the data buffers with the variables used in the vertex/fragment shader
void initTrack(){
	generateTrack();
	getAttiributeAndUniformIDTrack();
	//
	glGenBuffers(3, trackBuffersID);
	glBindBuffer( GL_ARRAY_BUFFER, trackBuffersID[0] );
	glBufferData( GL_ARRAY_BUFFER, sizeof(trackVertices), trackVertices, GL_STATIC_DRAW );
	
	glBindBuffer( GL_ARRAY_BUFFER, trackBuffersID[1] );
	glBufferData( GL_ARRAY_BUFFER, sizeof(track_texcoords), track_texcoords, GL_STATIC_DRAW );
	
	glBindBuffer( GL_ARRAY_BUFFER, trackBuffersID[2] );
	glBufferData( GL_ARRAY_BUFFER, sizeof(trackNormals), trackNormals, GL_STATIC_DRAW );
	
	glGenTextures(1, &textureID_track);
	glBindTexture(GL_TEXTURE_2D, textureID_track);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, track.width, track.height, 0, GL_RGB,  GL_UNSIGNED_BYTE, track.pixel_data);
	
	//which data are we going to use for positions
	glBindBuffer(GL_ARRAY_BUFFER, trackBuffersID[0]);
	glEnableVertexAttribArray(attibuteID_track[0]);
	// Describe our vertices array to OpenGL (it can't guess its format automatically)
	glVertexAttribPointer(attibuteID_track[0], 3, GL_FLOAT, GL_FALSE, 0, 0 );
	
	//which data are we going to use for texccords
	glBindBuffer(GL_ARRAY_BUFFER, trackBuffersID[1]);
	glEnableVertexAttribArray(attibuteID_track[1]);
	glVertexAttribPointer(attibuteID_track[1], 2, GL_FLOAT, GL_FALSE,0,0);
	
}

//draw the track on the scene
void drawTrack(){
	glUseProgram(programID2);
	glBindVertexArray(vao[2]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID_track);
	glUniform1i(uniformMatrixID_track[2], /*GL_TEXTURE*/0);

	glDrawArrays(GL_QUADS, 0,1440);
}

//generate the track ground
//obtain the attributes and uniforms names
//create the track VBOs, store the data within it
//linkt the data buffers with the variables used in the vertex/fragment shader
void initGround(){
	generateGround();
	getAttiributeAndUniformIDGround();
	//
	glGenBuffers(3, groundBuffersID);
	glBindBuffer( GL_ARRAY_BUFFER, groundBuffersID[0] );
	glBufferData( GL_ARRAY_BUFFER, sizeof(groundVertices), groundVertices, GL_STATIC_DRAW );
	
	glBindBuffer( GL_ARRAY_BUFFER, groundBuffersID[1] );
	glBufferData( GL_ARRAY_BUFFER, sizeof(ground_texcoords), ground_texcoords, GL_STATIC_DRAW );
	
	glBindBuffer( GL_ARRAY_BUFFER, groundBuffersID[2] );
	glBufferData( GL_ARRAY_BUFFER, sizeof(groundNormals), groundNormals, GL_STATIC_DRAW );
	
	glGenTextures(1, &textureID_ground);
	glBindTexture(GL_TEXTURE_2D, textureID_ground);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ground.width, ground.height, 0, GL_RGB,  GL_UNSIGNED_BYTE, ground.pixel_data);
	
	
	
	//which data are we going to use for positions
	glBindBuffer(GL_ARRAY_BUFFER, groundBuffersID[0]);
	glEnableVertexAttribArray(attibuteID_ground[0]);
	// Describe our vertices array to OpenGL (it can't guess its format automatically)
	glVertexAttribPointer(attibuteID_ground[0], 3, GL_FLOAT, GL_FALSE, 0, 0 );
	
	//which data are we going to use for texccords
	glBindBuffer(GL_ARRAY_BUFFER, groundBuffersID[1]);
	glEnableVertexAttribArray(attibuteID_ground[1]);
	glVertexAttribPointer(attibuteID_ground[1], 2, GL_FLOAT, GL_FALSE,0,0);
	
}

//draw the ground on the scene
void drawGround(){
	
	glUseProgram(programID1);
	glBindVertexArray(vao[1]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID_ground);
	glUniform1i(uniformMatrixID_ground[2], /*GL_TEXTURE*/0);

	glDrawArrays(GL_QUADS, 0,4);
	
}

//generate the forest vertices
//obtain the attributes and uniforms names
//create the track VBOs, store the data within it
//linkt the data buffers with the variables used in the vertex/fragment shader
void initForest(){
	generateForest();
	getAttiributeAndUniformIDForest();
	//
	glGenBuffers(3, forestBuffersID);
	glBindBuffer( GL_ARRAY_BUFFER, forestBuffersID[0] );
	glBufferData( GL_ARRAY_BUFFER, sizeof(forestVertices), forestVertices, GL_STATIC_DRAW );
	
	glBindBuffer( GL_ARRAY_BUFFER, forestBuffersID[1] );
	glBufferData( GL_ARRAY_BUFFER, sizeof(forest_texcoords), forest_texcoords, GL_STATIC_DRAW );
	
	glBindBuffer( GL_ARRAY_BUFFER, forestBuffersID[2] );
	glBufferData( GL_ARRAY_BUFFER, sizeof(forestNormals), forestNormals, GL_STATIC_DRAW );
	
	glGenTextures(1, &textureID_forest);
	glBindTexture(GL_TEXTURE_2D, textureID_forest);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, forest.width, forest.height, 0, GL_RGB,  GL_UNSIGNED_BYTE, forest.pixel_data);
	
	//which data are we going to use for positions
	glBindBuffer(GL_ARRAY_BUFFER, forestBuffersID[0]);
	glEnableVertexAttribArray(attibuteID_forest[0]);
	// Describe our vertices array to OpenGL (it can't guess its format automatically)
	glVertexAttribPointer(attibuteID_forest[0], 3, GL_FLOAT, GL_FALSE, 0, 0 );
	
	//which data are we going to use for texccords
	glBindBuffer(GL_ARRAY_BUFFER, forestBuffersID[1]);
	glEnableVertexAttribArray(attibuteID_forest[1]);
	glVertexAttribPointer(attibuteID_forest[1], 2, GL_FLOAT, GL_FALSE,0,0);
}

//draw the forest on the scene
void drawForest(){
	glUseProgram(programID3);
	glBindVertexArray(vao[4]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID_forest);
	glUniform1i(uniformMatrixID_forest[2], /*GL_TEXTURE*/0);

	glDrawArrays(GL_QUADS, 0,16);
}

//generate the sky vertices
//obtain the attributes and uniforms names
//create the track VBOs, store the data within it
//linkt the data buffers with the variables used in the vertex/fragment shader
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

//draw the sky on the scene
void drawSky(){
	glUseProgram(programID4);
	glBindVertexArray(vao[5]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID_sky);
	glUniform1i(uniformMatrixID_sky[2], /*GL_TEXTURE*/0);

	glDrawArrays(GL_QUADS, 0, 4);
}

//generate the track steering wheel
//obtain the attributes and uniforms names
//create the track VBOs, store the data within it
//linkt the data buffers with the variables used in the vertex/fragment shader
void initInterior(){
	generateInterior();
	getAttiributeAndUniformIDInterior();
	//
	glGenBuffers(2, interiorBuffersID);
	glBindBuffer( GL_ARRAY_BUFFER, interiorBuffersID[0] );
	glBufferData( GL_ARRAY_BUFFER, sizeof(interiorVertices), interiorVertices, GL_STATIC_DRAW );
	
	glBindBuffer( GL_ARRAY_BUFFER, interiorBuffersID[1] );
	glBufferData( GL_ARRAY_BUFFER, sizeof(interior_texcoords), interior_texcoords, GL_STATIC_DRAW );
	
	glGenTextures(1, &textureID_interior);
	glBindTexture(GL_TEXTURE_2D, textureID_interior);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, car_interior.width, car_interior.height, 0, GL_RGB,  GL_UNSIGNED_BYTE, car_interior.pixel_data);
	
	//which data are we going to use for positions
	glBindBuffer(GL_ARRAY_BUFFER, interiorBuffersID[0]);
	glEnableVertexAttribArray(attibuteID_interior[0]);
	// Describe our vertices array to OpenGL (it can't guess its format automatically)
	glVertexAttribPointer(attibuteID_interior[0], 3, GL_FLOAT, GL_FALSE, 0, 0 );
	
	//which data are we going to use for texccords
	glBindBuffer(GL_ARRAY_BUFFER, interiorBuffersID[1]);
	glEnableVertexAttribArray(attibuteID_interior[1]);
	glVertexAttribPointer(attibuteID_interior[1], 2, GL_FLOAT, GL_FALSE,0,0);
}

//draw the steering wheel on the scene
void drawInterior(){
	glUseProgram(programID5);
	glBindVertexArray(vao[6]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID_interior);
	glUniform1i(uniformMatrixID_interior[2], /*GL_TEXTURE*/0);

	glDrawArrays(GL_QUADS, 0, 4);
}


// I have used the same structures which are used in UsingNateRobbinsOBJReader/view_modelv4 (only used for the car and house model)
struct model_info {
//vertex data and indices
GLuint vbo_model_vertices;
GLuint *ibo_model_elements; //array of ibo "names" one for each group
GLuint **ibo_model_buffer; //array of ibo_buffers - one buffer for each group
//texture data and indices
GLuint vbo_model_texcoords;
GLuint *model_texture_ids; //array of texture "names" one for each group
GLfloat * vpositions;
GLfloat * tcoords;
} my_model, my_modelHouse;

//our shader program and it's related info
struct shader_program_info {
GLuint program;
GLuint attribute_coord3d;
GLuint attribute_texcoord;
GLuint uniform_Kd;
GLuint uniform_mv;
GLuint uniform_projection;
GLuint uniform_texture;
} my_program, my_programHouse;


//read the object, normalize the object vertices  and extract the object normals
 GLMmodel* myReadObj(char* fileName){
	GLMmodel* obj;
	obj = glmReadOBJ(fileName);
	glmUnitize(obj);
	
	glmFacetNormals(obj);
    glmVertexNormals(obj, 90.0);
	return obj;
}

//tranfer the data (texcoords and verticesCoordinates) from the GLMmodel (model_ptr) to a instance of model_info (my_model)
//model_ptr contains all information to draw the car
void storeDataCar(){
	my_model.vpositions=  (GLfloat *) malloc(sizeof(GLfloat)*model_ptr->numtriangles*3*3);
	my_model.tcoords=  (GLfloat *) malloc(sizeof(GLfloat)*model_ptr->numtriangles*3*2);
	
	for (int i=0;i<model_ptr->numtriangles;i++)
   {
     my_model.tcoords[i*2*3+0]=model_ptr->texcoords[model_ptr->triangles[i].tindices[0]*2+0];
     my_model.tcoords[i*2*3+1]=model_ptr->texcoords[model_ptr->triangles[i].tindices[0]*2+1];

     my_model.tcoords[i*2*3+2]=model_ptr->texcoords[model_ptr->triangles[i].tindices[1]*2+0];
     my_model.tcoords[i*2*3+3]=model_ptr->texcoords[model_ptr->triangles[i].tindices[1]*2+1];

     my_model.tcoords[i*2*3+4]=model_ptr->texcoords[model_ptr->triangles[i].tindices[2]*2+0];
     my_model.tcoords[i*2*3+5]=model_ptr->texcoords[model_ptr->triangles[i].tindices[2]*2+1];

     my_model.vpositions[i*3*3+0]=model_ptr->vertices[model_ptr->triangles[i].vindices[0]*3+0];
     my_model.vpositions[i*3*3+1]=model_ptr->vertices[model_ptr->triangles[i].vindices[0]*3+1];
     my_model.vpositions[i*3*3+2]=model_ptr->vertices[model_ptr->triangles[i].vindices[0]*3+2];

     my_model.vpositions[i*3*3+3]=model_ptr->vertices[model_ptr->triangles[i].vindices[1]*3+0];
     my_model.vpositions[i*3*3+4]=model_ptr->vertices[model_ptr->triangles[i].vindices[1]*3+1];
     my_model.vpositions[i*3*3+5]=model_ptr->vertices[model_ptr->triangles[i].vindices[1]*3+2];

     my_model.vpositions[i*3*3+6]=model_ptr->vertices[model_ptr->triangles[i].vindices[2]*3+0];
     my_model.vpositions[i*3*3+7]=model_ptr->vertices[model_ptr->triangles[i].vindices[2]*3+1];
     my_model.vpositions[i*3*3+8]=model_ptr->vertices[model_ptr->triangles[i].vindices[2]*3+2];

   }

	
}

//tranfer the data (texcoords and verticesCoordinates) from the GLMmodel (model_house) to a instance of model_info (my_modelHouse)
//model_house contains all information to draw the house
void storeDataHouse(){
	my_modelHouse.vpositions=  (GLfloat *) malloc(sizeof(GLfloat)*model_house->numtriangles*3*3);
	my_modelHouse.tcoords=  (GLfloat *) malloc(sizeof(GLfloat)*model_house->numtriangles*3*2);
	
	for (int i=0;i<model_house->numtriangles;i++)
   {
     my_modelHouse.tcoords[i*2*3+0]=model_house->texcoords[model_house->triangles[i].tindices[0]*2+0];
     my_modelHouse.tcoords[i*2*3+1]=model_house->texcoords[model_house->triangles[i].tindices[0]*2+1];

     my_modelHouse.tcoords[i*2*3+2]=model_house->texcoords[model_house->triangles[i].tindices[1]*2+0];
     my_modelHouse.tcoords[i*2*3+3]=model_house->texcoords[model_house->triangles[i].tindices[1]*2+1];

     my_modelHouse.tcoords[i*2*3+4]=model_house->texcoords[model_house->triangles[i].tindices[2]*2+0];
     my_modelHouse.tcoords[i*2*3+5]=model_house->texcoords[model_house->triangles[i].tindices[2]*2+1];

     my_modelHouse.vpositions[i*3*3+0]=model_house->vertices[model_house->triangles[i].vindices[0]*3+0];
     my_modelHouse.vpositions[i*3*3+1]=model_house->vertices[model_house->triangles[i].vindices[0]*3+1];
     my_modelHouse.vpositions[i*3*3+2]=model_house->vertices[model_house->triangles[i].vindices[0]*3+2];

     my_modelHouse.vpositions[i*3*3+3]=model_house->vertices[model_house->triangles[i].vindices[1]*3+0];
     my_modelHouse.vpositions[i*3*3+4]=model_house->vertices[model_house->triangles[i].vindices[1]*3+1];
     my_modelHouse.vpositions[i*3*3+5]=model_house->vertices[model_house->triangles[i].vindices[1]*3+2];

     my_modelHouse.vpositions[i*3*3+6]=model_house->vertices[model_house->triangles[i].vindices[2]*3+0];
     my_modelHouse.vpositions[i*3*3+7]=model_house->vertices[model_house->triangles[i].vindices[2]*3+1];
     my_modelHouse.vpositions[i*3*3+8]=model_house->vertices[model_house->triangles[i].vindices[2]*3+2];

   }

	
}

//obtation of the attributes and uniforms of car
int getAttiributeAndUniformIDCar(){
	const char* attribute_name;
	attribute_name = "coord3d";
	my_program.attribute_coord3d = glGetAttribLocation(my_program.program, attribute_name);
	if (my_program.attribute_coord3d == -1) {
		cerr << "Could not bind attribute " << attribute_name << endl;
		return 0;
	}
	attribute_name = "vtexcoords";
	my_program.attribute_texcoord = glGetAttribLocation(my_program.program, attribute_name);
	if (my_program.attribute_texcoord == -1) {
		cerr << "Could not bind attribute " << attribute_name << endl;
		return 0;
	}
	const char* uniform_name;
	uniform_name = "mv";
	my_program.uniform_mv = glGetUniformLocation(my_program.program, uniform_name);
	if (my_program.uniform_mv == -1) {
		cerr << "Could not bind uniform " <<  uniform_name << endl;
		return 0;
	}
	
	uniform_name = "projection";
	my_program.uniform_projection = glGetUniformLocation(my_program.program, uniform_name);
	if (my_program.uniform_projection == -1) {
		cerr << "Could not bind uniform " <<  uniform_name << endl;
		return 0;
	}


	uniform_name = "Kd";
	my_program.uniform_Kd = glGetUniformLocation(my_program.program, uniform_name);
	if (my_program.uniform_Kd == -1) {
		cerr << "Could not bind uniform " <<  uniform_name << endl;
		//return 0;
	}
	uniform_name = "mytexture";
	my_program.uniform_texture = glGetUniformLocation(my_program.program, uniform_name);
	if (my_program.uniform_texture == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
		return 0;
	}
	  return 1;
}

//obtation of the attributes and uniforms of house
int getAttiributeAndUniformIDHouse(){
	const char* attribute_name;
	attribute_name = "coord3d";
	my_programHouse.attribute_coord3d = glGetAttribLocation(my_programHouse.program, attribute_name);
	if (my_programHouse.attribute_coord3d == -1) {
		cerr << "house: Could not bind attribute " << attribute_name << endl;
		return 0;
	}
	attribute_name = "vtexcoords";
	my_programHouse.attribute_texcoord = glGetAttribLocation(my_programHouse.program, attribute_name);
	if (my_programHouse.attribute_texcoord == -1) {
		cerr << "house: Could not bind attribute " << attribute_name << endl;
		return 0;
	}
	const char* uniform_name;
	uniform_name = "mv";
	my_programHouse.uniform_mv = glGetUniformLocation(my_programHouse.program, uniform_name);
	if (my_programHouse.uniform_mv == -1) {
		cerr << "house: Could not bind uniform " <<  uniform_name << endl;
		return 0;
	}
	
	uniform_name = "projection";
	my_programHouse.uniform_projection = glGetUniformLocation(my_programHouse.program, uniform_name);
	if (my_programHouse.uniform_projection == -1) {
		cerr << "house: Could not bind uniform " <<  uniform_name << endl;
		return 0;
	}


	uniform_name = "Kd";
	my_programHouse.uniform_Kd = glGetUniformLocation(my_programHouse.program, uniform_name);
	if (my_programHouse.uniform_Kd == -1) {
		cerr << "house: Could not bind uniform " <<  uniform_name << endl;
		//return 0;
	}
	uniform_name = "mytexture";
	my_programHouse.uniform_texture = glGetUniformLocation(my_programHouse.program, uniform_name);
	if (my_programHouse.uniform_texture == -1) {
		fprintf(stderr, "house: Could not bind uniform %s\n", uniform_name);
		return 0;
	}
	  return 1;
}

//obtain the house data from .obj/.mtl
//obtain the attributes and uniforms names
//create the track VBOs, store the data within it
void initHouse(){
	model_house = myReadObj("house/House2.obj");
	storeDataHouse();
	
	glGenBuffers(1, &(my_modelHouse.vbo_model_vertices));
	glBindBuffer(GL_ARRAY_BUFFER, my_modelHouse.vbo_model_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(*(my_modelHouse.vpositions))*(model_house->numtriangles)*3*3, my_modelHouse.vpositions, GL_STATIC_DRAW);
	  
	glGenBuffers(1, &(my_modelHouse.vbo_model_texcoords));
	glBindBuffer(GL_ARRAY_BUFFER, my_modelHouse.vbo_model_texcoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(*(my_modelHouse.tcoords))*(model_house->numtriangles)*3*2, my_modelHouse.tcoords, GL_STATIC_DRAW);

	my_modelHouse.ibo_model_elements= (GLuint *) malloc(sizeof(GLuint)*model_house->numgroups);
	glGenBuffers(model_house->numgroups, my_modelHouse.ibo_model_elements);
	my_modelHouse.ibo_model_buffer= (GLuint **) malloc(sizeof(GLuint *)*model_house->numgroups);
	  
	my_modelHouse.model_texture_ids= (GLuint *) malloc(sizeof(GLuint)*model_house->numgroups);  
	GLMgroup* group=model_house->groups;
	
	int current_group=0;
	while (group)
	{ 
		if ((group->numtriangles) ==0 ) //have nothing to draw
		{
			group=group->next;
			current_group++;
			break;
		}
	   //if look at code - for some reason the numtriangles is one more than actual and vertex,normals, and texcoords arrays have nothing in first 3 places in array.....almost certainly because OBJ indices start from 1 whereas C indices start from 0
		//std::cerr << "will draw  " << group->numtriangles << " triangles" << std::endl;
		//std::cerr << "from (for all groups)  " << model_ptr->numvertices << " vertices" << std::endl;
		if (model_house->materials)
		{
			//std::cerr << "with material Kd " << 
			//model_ptr->materials[group->material].diffuse[0]  << " "
			//<<
			//model_ptr->materials[group->material].diffuse[1]  << " "
			//<<
			//model_ptr->materials[group->material].diffuse[2] 
			//<< std::endl;
			if (model_house->materials[group->material].map_Kd_file)
		   {
				//std::cerr << "and map Kd file " << model_ptr->materials[group->material].map_Kd_file << std::endl;

				my_modelHouse.model_texture_ids[current_group]= SOIL_load_OGL_texture
				(
					model_house->materials[group->material].map_Kd_file,
					SOIL_LOAD_AUTO,
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
				);
				if (my_modelHouse.model_texture_ids[current_group])
				std::cerr << " loaded texture " << model_house->materials[group->material].map_Kd_file << "ok" << std::endl;
				else
				std::cerr << " failed to load texture " << model_house->materials[group->material].map_Kd_file << std::endl;
		   }
		} //end group not empty
		
	//now the data for a group is actually an index into a triangle which is then something that gives three indices into our vertex array. 

		my_modelHouse.ibo_model_buffer[current_group] = (GLuint *) malloc(sizeof(GLuint)*3*(group->numtriangles));
		for (int i=0;i<(group->numtriangles);i++)
		{
			my_modelHouse.ibo_model_buffer[current_group][3*i+0]=group->triangles[i]*3+0;
			my_modelHouse.ibo_model_buffer[current_group][3*i+1]=group->triangles[i]*3+1;
			my_modelHouse.ibo_model_buffer[current_group][3*i+2]=group->triangles[i]*3+2;
		}
		//now we say we will refer to this buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_modelHouse.ibo_model_elements[current_group]);
		//for this buffer we say what the buffer looks like and where it lives
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*3*(group->numtriangles), my_modelHouse.ibo_model_buffer[current_group], GL_STATIC_DRAW);

		group=group->next;
		current_group++;
	} //end looping over groups

	glUseProgram(my_programHouse.program);
	
	getAttiributeAndUniformIDHouse();


}

//obtain the car data from .obj/.mtl
//obtain the attributes and uniforms names
//create the track VBOs, store the data within it
void initCar()
{
	
	model_ptr = myReadObj("car/car-n.obj");	
	storeDataCar();
	
	glGenBuffers(1, &(my_model.vbo_model_vertices));
	glBindBuffer(GL_ARRAY_BUFFER, my_model.vbo_model_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(*(my_model.vpositions))*(model_ptr->numtriangles)*3*3, my_model.vpositions, GL_STATIC_DRAW);
	  
	glGenBuffers(1, &(my_model.vbo_model_texcoords));
	glBindBuffer(GL_ARRAY_BUFFER, my_model.vbo_model_texcoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(*(my_model.tcoords))*(model_ptr->numtriangles)*3*2, my_model.tcoords, GL_STATIC_DRAW);

	my_model.ibo_model_elements= (GLuint *) malloc(sizeof(GLuint)*model_ptr->numgroups);
	glGenBuffers(model_ptr->numgroups, my_model.ibo_model_elements);
	my_model.ibo_model_buffer= (GLuint **) malloc(sizeof(GLuint *)*model_ptr->numgroups);
	  
	my_model.model_texture_ids= (GLuint *) malloc(sizeof(GLuint)*model_ptr->numgroups);  
	GLMgroup* group=model_ptr->groups;
	
	int current_group=0;
	while (group)
	{ 
		if ((group->numtriangles) ==0 ) //have nothing to draw
		{
			group=group->next;
			current_group++;
			break;
		}
	   //if look at code - for some reason the numtriangles is one more than actual and vertex,normals, and texcoords arrays have nothing in first 3 places in array.....almost certainly because OBJ indices start from 1 whereas C indices start from 0
		//std::cerr << "will draw  " << group->numtriangles << " triangles" << std::endl;
		//std::cerr << "from (for all groups)  " << model_ptr->numvertices << " vertices" << std::endl;
		if (model_ptr->materials)
		{
			//std::cerr << "with material Kd " << 
			//model_ptr->materials[group->material].diffuse[0]  << " "
			//<<
			//model_ptr->materials[group->material].diffuse[1]  << " "
			//<<
			//model_ptr->materials[group->material].diffuse[2] 
			//<< std::endl;
			if (model_ptr->materials[group->material].map_Kd_file)
		   {
				//std::cerr << "and map Kd file " << model_ptr->materials[group->material].map_Kd_file << std::endl;

				my_model.model_texture_ids[current_group]= SOIL_load_OGL_texture
				(
					model_ptr->materials[group->material].map_Kd_file,
					SOIL_LOAD_AUTO,
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
				);
				if (my_model.model_texture_ids[current_group])
				std::cerr << " loaded texture " << model_ptr->materials[group->material].map_Kd_file << "ok" << std::endl;
				else
				std::cerr << " failed to load texture " << model_ptr->materials[group->material].map_Kd_file << std::endl;
		   }
		} //end group not empty
		
	//now the data for a group is actually an index into a triangle which is then something that gives three indices into our vertex array. 

		my_model.ibo_model_buffer[current_group] = (GLuint *) malloc(sizeof(GLuint)*3*(group->numtriangles));
		for (int i=0;i<(group->numtriangles);i++)
		{
			my_model.ibo_model_buffer[current_group][3*i+0]=group->triangles[i]*3+0;
			my_model.ibo_model_buffer[current_group][3*i+1]=group->triangles[i]*3+1;
			my_model.ibo_model_buffer[current_group][3*i+2]=group->triangles[i]*3+2;
		}
		//now we say we will refer to this buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_model.ibo_model_elements[current_group]);
		//for this buffer we say what the buffer looks like and where it lives
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*3*(group->numtriangles), my_model.ibo_model_buffer[current_group], GL_STATIC_DRAW);

		group=group->next;
		current_group++;
	} //end looping over groups
	
	
	glUseProgram(my_program.program);
	
	getAttiributeAndUniformIDCar();
	
}


//generate or read files, in order to obtain the information to draw the objects in the scene
void init(){
	
	//I have used the same vertex and fragment shader for the statics objects.
	
	glGenVertexArrays( 7, vao );
	
	glBindVertexArray(vao[0]);
	my_program.program = InitShader("vCar.glsl","fCar.glsl");
	glUseProgram(my_program.program);
	initCar();
	
	glBindVertexArray(vao[1]);
	programID1 = InitShader("vStatic.glsl","fStatic.glsl");
	glUseProgram(programID1);
	initGround();
	
	glBindVertexArray(vao[2]);
	programID2 = InitShader("vStatic.glsl","fStatic.glsl");
	glUseProgram(programID2);
	initTrack();
	
	glBindVertexArray(vao[3]);
	my_programHouse.program = InitShader("vHouse.glsl","fHouse.glsl");
	glUseProgram(my_programHouse.program);
	initHouse();
	
	glBindVertexArray(vao[4]);
	programID3 = InitShader("vStatic.glsl","fStatic.glsl");
	glUseProgram(programID3);
	initForest();
	
	glBindVertexArray(vao[5]);
	programID4 = InitShader("vStatic.glsl","fStatic.glsl");
	glUseProgram(programID4);
	initSky();
	
	glBindVertexArray(vao[6]);
	programID5 = InitShader("vStatic.glsl","fStatic.glsl"); 
	glUseProgram(programID5);
	initInterior();
}

//draw the car on the scene
void drawCar(){
	
	//loop through groups
	GLMgroup* group=model_ptr->groups;
    int current_group=0;
    while (group)
      { 
     if ((group->numtriangles) ==0 ) //have nothing to draw
          {
        group=group->next;
        current_group++;
          break;
          }
 
  /* Push each element in buffer_vertices to the vertex shader */
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_model.ibo_model_elements[current_group]);
  //how many elements in what we want to draw?? Sure, we could have kept this as state rather than enquiring now.....
  int size;  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

    glUniform3fv(my_program.uniform_Kd,1,(const GLfloat *)  &(model_ptr->materials[group->material].diffuse));

  glBindTexture(GL_TEXTURE_2D, my_model.model_texture_ids[current_group]);
   glUniform1i(my_program.uniform_texture, /*GL_TEXTURE*/0); 

   glDrawElements(GL_TRIANGLES, size/sizeof(GLuint), GL_UNSIGNED_INT, 0);
        group=group->next;
        current_group++;
   }//end looping through groups
	
}

//draw the car on the house
void drawHouse(){
		//loop through groups
	GLMgroup* group=model_house->groups;
    int current_group=0;
    while (group)
      { 
     if ((group->numtriangles) ==0 ) //have nothing to draw
          {
        group=group->next;
        current_group++;
          break;
          }
 
  /* Push each element in buffer_vertices to the vertex shader */
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_modelHouse.ibo_model_elements[current_group]);
  //how many elements in what we want to draw?? Sure, we could have kept this as state rather than enquiring now.....
  int size;  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

    glUniform3fv(my_programHouse.uniform_Kd,1,(const GLfloat *)  &(model_house->materials[group->material].diffuse));

	glBindTexture(GL_TEXTURE_2D, my_modelHouse.model_texture_ids[current_group]);
	glUniform1i(my_programHouse.uniform_texture, /*GL_TEXTURE*/0); 

   glDrawElements(GL_TRIANGLES, size/sizeof(GLuint), GL_UNSIGNED_INT, 0);
        group=group->next;
        current_group++;
   }//end looping through groups


}


void onIdle() {
	//update the car position
	//update the car orientation
	CarX = rx_elipse_car * cos(step * iter);
	CarZ = ry_elipse_car * sin(step * iter);
	angle = -step * iter * (180/M_PI);
  
	//camera that follow the car position from the top
	//obj1_x = rx_elipse_car * cos(step * (iter+5));
	//obj1_z = ry_elipse_car * sin(step * (iter+5));
	//obj1_x = 20 * cos(step * iter);
	//obj1_z = 20 * sin(step * iter);
	//eye1_x =  rx_elipse_car * cos(step * (iter-20));
	//eye1_z =  ry_elipse_car * sin(step * (iter-20));
	if(camera1Position == 0){
		eye1_x = 0.0f;
		eye1_y = 20.0f;
		eye1_z = 0.0f;

		obj1_x = 0;
		obj1_y = 0;
		obj1_z = 0;

		upx1 = 1;
		upy1 = 0;
		upz1 = 0;
	}
	if(camera1Position == 1){
		eye1_x = 0.0f;
		eye1_y = 10.0f;
		eye1_z = 0.0f;

		obj1_x = CarX;
		obj1_y = 0;
		obj1_z = CarZ;

		upx1 = 0;
		upy1 = 1;
		upz1 = 0;
	}
	
	if(camera1Position == 2){
		eye1_x = rx_elipse_car * cos(step * (iter-15));
		eye1_y = 2.0f;
		eye1_z = ry_elipse_car * sin(step * (iter-15));

		obj1_x = CarX;
		obj1_y = 1;
		obj1_z = CarZ;

		upx1 = 0;
		upy1 = 1;
		upz1 = 0;
	}
	camera1 = glm::lookAt(glm::vec3(eye1_x, eye1_y , eye1_z), glm::vec3(obj1_x, obj1_y, obj1_z), glm::vec3(upx1, upy1, upz1));
  
	//update the camera2 (view from inside the car)
	GLfloat eye2_x = CarX;
	GLfloat eye2_y = CarY;
	GLfloat eye2_z = CarZ;

	GLfloat obj2_x = rx_elipse_car * cos(step * (iter+10));
	GLfloat obj2_y = CarY;
	GLfloat obj2_z = ry_elipse_car * sin(step * (iter+10));
  
	camera2 = glm::lookAt(glm::vec3(eye2_x, eye2_y , eye2_z), glm::vec3(obj2_x, obj2_y, obj2_z), glm::vec3(upx2, upy2, upz2));
  
	
	iter++;
	if(iter >= 360){
		iter = 0;
	}
	glutPostRedisplay();//redisplay
}

void onDisplay()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); 
	glBindVertexArray(vao[0]);
	glUseProgram(my_program.program);
	
	glEnableVertexAttribArray(my_program.attribute_coord3d);
	glBindBuffer(GL_ARRAY_BUFFER, my_model.vbo_model_vertices);
	glVertexAttribPointer(my_program.attribute_coord3d, 3, GL_FLOAT, GL_FALSE,0, 0);
	
	glEnableVertexAttribArray(my_program.attribute_texcoord);
	glBindBuffer(GL_ARRAY_BUFFER, my_model.vbo_model_texcoords);
	glVertexAttribPointer(my_program.attribute_texcoord, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//I used "glViewport" to perform the split the window
	glViewport(0,(screen_height/2),screen_width,(screen_height/2));	
	
	//rotation matrix (y-axis)
	glm::vec3 axis_y(0, 1, 0);
	glm::mat4 anim = glm::rotate(glm::mat4(1.0f), angle, axis_y);

	//calculate the model-view matrices (camera1 and camera2) for all objects
	model_car = glm::translate(glm::mat4(1.0f), glm::vec3(CarX, CarY, CarZ));
	mv_car = camera1 * model_car * anim; 
	mv_car2 = camera2 * model_car * anim;
  
	model_ground = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));	
	mv_ground = camera1 * model_ground ;
	mv_ground = glm::scale(mv_ground,glm::vec3(groundScale,groundScale,groundScale)); 
	
	mv_ground2 = camera2 * model_ground ;
	mv_ground2 = glm::scale(mv_ground2,glm::vec3(groundScale,groundScale,groundScale));
	
	model_track = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.1, 0.0));	
	mv_track = camera1 * model_track ;
	mv_track2 = camera2 * model_track ;
	
	MatrixModelHouse = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 1.0, -5.8));
	mv_house = camera1 * MatrixModelHouse;
	mv_house = glm::scale(mv_house,glm::vec3(2.0,1.5,2.0));
  
	mv_house2 = camera2 * MatrixModelHouse;
	mv_house2 = glm::scale(mv_house2,glm::vec3(2.0,1.5,2.0));
	
	model_forest = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));	
	mv_forest = camera1 * model_forest ;// this is the overall transorm of our composited model - rotate it, translate it away from origin. Then position our viewer and set the projection.
	mv_forest = glm::scale(mv_forest,glm::vec3(groundScale,groundScale,groundScale)); 
	
	mv_forest2 = camera2 * model_forest ;
	mv_forest2 = glm::scale(mv_forest2,glm::vec3(groundScale,groundScale,groundScale));
	
	model_sky = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));	
	mv_sky = camera1 * model_sky ;
	mv_sky = glm::scale(mv_sky,glm::vec3(groundScale,groundScale,groundScale)); 
	
	mv_sky2 = camera2 * model_sky ;
	mv_sky2 = glm::scale(mv_sky2,glm::vec3(groundScale,groundScale,groundScale));
	
	model_Interior = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));
	mv_Interior = camera3 * model_Interior;
	mv_Interior = glm::scale(mv_Interior,glm::vec3(1.0,1.0,1.0));
	///////////////////


	//draw the car (camera 1)
	glUniformMatrix4fv(my_program.uniform_mv, 1, GL_FALSE, glm::value_ptr(mv_car));
	glUniformMatrix4fv(my_program.uniform_projection, 1, GL_FALSE, glm::value_ptr(projection));
	glActiveTexture(GL_TEXTURE0);
	drawCar();
   
	//draw the ground (camera 1)
	glBindVertexArray(vao[1]);
	glUseProgram(programID1);
	glBindBuffer(GL_ARRAY_BUFFER, groundBuffersID[0]);
   
	glUniformMatrix4fv(uniformMatrixID_ground[0], 1, GL_FALSE, glm::value_ptr(mv_ground));
	glUniformMatrix4fv(uniformMatrixID_ground[1], 1, GL_FALSE, glm::value_ptr(projection));
   
	drawGround();
   
	//draw the track (camera 1)
	glBindVertexArray(vao[2]);
	glUseProgram(programID2);
	glBindBuffer(GL_ARRAY_BUFFER, trackBuffersID[0]);
   
	glUniformMatrix4fv(uniformMatrixID_track[0], 1, GL_FALSE, glm::value_ptr(mv_track));
	glUniformMatrix4fv(uniformMatrixID_track[1], 1, GL_FALSE, glm::value_ptr(projection));
   
   
	drawTrack();
   
	//draw the House (camera 1)
   	glBindVertexArray(vao[3]);
	glUseProgram(my_programHouse.program);
	
	glEnableVertexAttribArray(my_programHouse.attribute_coord3d);
	glBindBuffer(GL_ARRAY_BUFFER, my_modelHouse.vbo_model_vertices);
	glVertexAttribPointer(my_programHouse.attribute_coord3d, 3, GL_FLOAT, GL_FALSE,0, 0);
	
	
	glEnableVertexAttribArray(my_programHouse.attribute_texcoord);
	glBindBuffer(GL_ARRAY_BUFFER, my_modelHouse.vbo_model_texcoords);
	glVertexAttribPointer(my_programHouse.attribute_texcoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
   
   	glUniformMatrix4fv(my_programHouse.uniform_mv, 1, GL_FALSE, glm::value_ptr(mv_house));
	glUniformMatrix4fv(my_programHouse.uniform_projection, 1, GL_FALSE, glm::value_ptr(projection));

	drawHouse();
	
	//draw the forest (camera 1)
	glBindVertexArray(vao[4]);
	glUseProgram(programID3);
	glBindBuffer(GL_ARRAY_BUFFER, forestBuffersID[0]);
   
	glUniformMatrix4fv(uniformMatrixID_forest[0], 1, GL_FALSE, glm::value_ptr(mv_forest));
	glUniformMatrix4fv(uniformMatrixID_forest[1], 1, GL_FALSE, glm::value_ptr(projection));
   
   
	drawForest();
	
	//draw the sky (camera 1)
	glBindVertexArray(vao[5]);
	glUseProgram(programID4);
	glBindBuffer(GL_ARRAY_BUFFER, skyBuffersID[0]);
   
	glUniformMatrix4fv(uniformMatrixID_sky[0], 1, GL_FALSE, glm::value_ptr(mv_sky));
	glUniformMatrix4fv(uniformMatrixID_sky[1], 1, GL_FALSE, glm::value_ptr(projection));
   
	drawSky();
	
	
	///////////////draw camera 2
	glViewport(0,screen_height/8,screen_width,screen_height/2.8);
	
	//draw the ground (camera 2)
	glBindVertexArray(vao[1]);
	glUseProgram(programID1);
	glBindBuffer(GL_ARRAY_BUFFER, groundBuffersID[0]);
   
	glUniformMatrix4fv(uniformMatrixID_ground[0], 1, GL_FALSE, glm::value_ptr(mv_ground2));
	glUniformMatrix4fv(uniformMatrixID_ground[1], 1, GL_FALSE, glm::value_ptr(projection));
   
   
	drawGround();
	
	//draw the track (camera 2)
	glBindVertexArray(vao[2]);
	glUseProgram(programID2);
	glBindBuffer(GL_ARRAY_BUFFER, trackBuffersID[0]);
   
	glUniformMatrix4fv(uniformMatrixID_track[0], 1, GL_FALSE, glm::value_ptr(mv_track2));
	glUniformMatrix4fv(uniformMatrixID_track[1], 1, GL_FALSE, glm::value_ptr(projection));
   
   
	drawTrack();

	//draw the House (camera 2)
	glBindVertexArray(vao[3]);
	glUseProgram(my_programHouse.program);

   	glUniformMatrix4fv(my_programHouse.uniform_mv, 1, GL_FALSE, glm::value_ptr(mv_house2));
	glUniformMatrix4fv(my_programHouse.uniform_projection, 1, GL_FALSE, glm::value_ptr(projection));

	drawHouse();

	//draw the forest (camera 2)
	glBindVertexArray(vao[4]);
	glUseProgram(programID3);
	glBindBuffer(GL_ARRAY_BUFFER, forestBuffersID[0]);
   
	glUniformMatrix4fv(uniformMatrixID_forest[0], 1, GL_FALSE, glm::value_ptr(mv_forest2));
	glUniformMatrix4fv(uniformMatrixID_forest[1], 1, GL_FALSE, glm::value_ptr(projection));
   
	drawForest();
	
	//draw the sky (camera 2)
	glBindVertexArray(vao[5]);
	glUseProgram(programID4);
	glBindBuffer(GL_ARRAY_BUFFER, skyBuffersID[0]);
   
	glUniformMatrix4fv(uniformMatrixID_sky[0], 1, GL_FALSE, glm::value_ptr(mv_sky2));
	glUniformMatrix4fv(uniformMatrixID_sky[1], 1, GL_FALSE, glm::value_ptr(projection));
   
	drawSky();
	
	
	//in order to create the driver's view a create, I create other subregion (glViewport) using  inside the bottom view
	//I know that you have suggested using a occlusion mask, but I thought that is easier  implement the driver view this way

	//draw the steering wheel
	glViewport(0,0,screen_width,screen_height/8);
	glBindVertexArray(vao[6]);
	glUseProgram(programID5);
	glBindBuffer(GL_ARRAY_BUFFER, interiorBuffersID[0]);
	glUniformMatrix4fv(uniformMatrixID_interior[0], 1, GL_FALSE, glm::value_ptr(mv_Interior));
	glUniformMatrix4fv(uniformMatrixID_interior[1], 1, GL_FALSE, glm::value_ptr(projection));
	
	drawInterior();
	
	glutSwapBuffers();
}

void onReshape(int width, int height) {
  screen_width = width;
  screen_height = height;
  glViewport(0, 0, screen_width, screen_height);
}

void free_resources()
{
  glDeleteProgram(my_program.program);
  glDeleteBuffers(1, &(my_model.vbo_model_vertices));
  glDeleteBuffers(model_ptr->numgroups, my_model.ibo_model_elements);
  glmDelete(model_ptr); //finished with it....
}

void keyPressed (unsigned char key, int x, int y) {
	if (key == 'c') { 
		camera1Position++;
		if(camera1Position>=3)camera1Position=0;
	}
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
    glutKeyboardFunc(keyPressed);
    glutMainLoop();
  

  free_resources();
  return 0;
}
