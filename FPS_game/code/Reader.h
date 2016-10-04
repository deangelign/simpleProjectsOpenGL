#ifndef __READER_H__
#define __READER_H__

#ifndef __APPLE__
/* Use glew.h instead of gl.h to get all the GL prototypes declared */
#include <GL/glew.h>
/* Using the GLUT library for the base windowing setup */
#include <GL/glut.h>
#else
#include<OpenGL/gl3.h>
#include<GLUT/glut.h>
#endif

#include "external_files/SOIL/SOIL.h"
/* Nate Robbins glm */
#include "external_files/glm_mod.h"
#include "external_files/InitShader.cpp"

#include "external_files/glm/glm.hpp"
#include "external_files/glm/gtc/matrix_transform.hpp"
#include "external_files/glm/gtc/type_ptr.hpp"
#include "external_files/glm/matrix.hpp"


class Reader{
private:
	
public:
	Reader();
	void storeData();
	int getAttiributeAndUniformIDs();
	GLMmodel* myReadObj(char* fileName);
	void draw(glm::mat4 view, glm::mat4 projection);
	void init(char* fileName,const char* vertexShaderFileName,const char* fragmentShaderFileName);
	GLMmodel* model_ptr;
	GLuint vao;
	GLuint vbo_model_vertices;
	GLuint vbo_model_normal;
	GLuint *ibo_model_elements; //array of ibo "names" one for each group
	GLuint **ibo_model_buffer; //array of ibo_buffers - one buffer for each group
//texture data and indices
	GLuint vbo_model_texcoords;
	GLuint *model_texture_ids; //array of texture "names" one for each group
	GLfloat * vpositions;
	GLfloat * tcoords;
	GLfloat * vNormal;
	
	GLuint program;
	GLuint attribute_coord3d;
	GLuint attribute_texcoord;
	GLuint attribute_normal;
	GLuint uniform_Kd;
	GLuint uniform_m;
	GLuint uniform_v;
	GLuint uniform_projection;
	GLuint uniform_texture;
	GLuint uniform_m_3x3_inv_transp;
	GLuint uniform_v_inv;
	GLuint uniform_alpha;
	GLuint uniform_overrideColor;
};


#endif
