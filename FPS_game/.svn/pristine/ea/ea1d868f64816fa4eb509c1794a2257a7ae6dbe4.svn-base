#include "MyMesh.h"
#include <iostream>

//The purpose of this file is being a class that all other files include it.
//Using this class you can store the data from one or more objects in grapichs cards.
//There are many variables to store the data of one or more models .

using namespace std;

//default constructor
MyMesh::MyMesh(){
	this->lastVAO_ID = -1;
	this->modelMatrix = glm::mat4(1.0f);
	this->reader;
}


glm::vec4 MyMesh::getVertice(int index){
	if(index < 0 || index >= this->vertices.size()){
		cout << "invalid position in vertices for index = " << index << endl;
		return glm::vec4(0.0f);
	}
	return this->vertices.at(index);
}

glm::vec3 MyMesh::getNormal(int index){
	if(index < 0 || index >= this->normals.size()){
		cout << "invalid position in normals for index = " << index << endl;
		return glm::vec3(0.0f);
	}
	return this->normals.at(index);
}

glm::vec2 MyMesh::getTextureCoordenate(int index){
	if(index < 0 || index >= this->textureCoordenates.size()){
		cout << "invalid position in textureCoordenates for index = " << index << endl;
		return glm::vec2(0.0f);
	}
	return this->textureCoordenates.at(index);
}

glm::vec3 MyMesh::getTangents(int index){
	if(index < 0 || index >= this->tangents.size()){
		cout << "invalid position in tangents for index = " << index << endl;
		return glm::vec3(0.0f);
	}
	return this->tangents.at(index);
}

GLushort MyMesh::getElement(int index){
	if(index < 0 || index >= this->elements.size()){
		cout << "invalid position in elements for index = " << index << endl;
		return -1;
	}
	return this->elements.at(index);
}

//add the name of a texture file in the vector textureFilesName
void MyMesh::addTextureFilesName(const char* fileName){
	this->textureFilesName.push_back(fileName);
}

vector<glm::vec4> MyMesh::getVectorVertices(){
	return this->vertices;
}

vector<glm::vec3> MyMesh::getVectorNormals(){
	return this->normals;
}

vector<glm::vec2> MyMesh::getVectorTextureCoordenates(){
	return this->textureCoordenates;
}

vector<glm::vec3> MyMesh::getVectorTangents(){
	return this->tangents;
}

vector<GLushort> MyMesh::getVectorElements(){
	return this->elements;
}

glm::mat4 MyMesh::getModelMatrix(){
	return this-> modelMatrix;
}

//add a vectice Coordinate in the vector vertices
void MyMesh::addVertice(glm::vec4 verticeCoordenates){
	this->vertices.push_back(verticeCoordenates);
}

//add a normal Coordinate in the vector normals
void MyMesh::addNormal(glm::vec3 verticeNormal){
	this->normals.push_back(verticeNormal);
}

//add a texture Coordinate in vector vertices
void MyMesh::addTextureCoordenate(glm::vec2 _textureCoordenates){
	this->textureCoordenates.push_back(_textureCoordenates);
}

void MyMesh::addElement(GLushort element){
	this->elements.push_back(element);
}

void MyMesh::setVectorVertices(vector<glm::vec4> _vertices){
	this->vertices = _vertices;
}

void MyMesh::setVectorNormals(vector<glm::vec3> _normals){
	this->normals = _normals;
}

void MyMesh::setVectorTextureCoordenates(vector<glm::vec2> _textureCoordenatesVector){
	this->textureCoordenates = _textureCoordenatesVector;
}

void MyMesh::setVectorTangents(vector<glm::vec3>_tangents){
	this->tangents = _tangents;
}

void MyMesh::setVectorElement(vector<GLushort>_elements){
	this->elements = _elements;
}

void MyMesh::setTextureID(int index,GLuint textureID){
	this->textureIds.at(index) = textureID;
}


void MyMesh::setModelMatrix(glm::mat4 _modelMatrix){
		
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
				this->modelMatrix[i][j] = _modelMatrix[i][j];
		}
	}
	
	
}

//store the data in graphics cards
//I have implemented this method only to make shorter my code
void MyMesh::storeDataInBuffer(GLuint VAO_ID,GLuint VBO_ID,GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage){
	//if(!(lastVAO_ID == VAO_ID)){
		
		glBindVertexArray(VAO_ID);
		lastVAO_ID = VAO_ID;
	//}
	glBindBuffer(target, VBO_ID);
	glBufferData(target, size, data, usage);
}

GLuint MyMesh::getVertexArrayObjectId(int index){
	if(index < 0 || index >= this->vertexArrayObjectIds.size()){
		cout << "invalid position in VertexArrayObjectId for index = " << index << endl;
		return 0;
	}
	return this->vertexArrayObjectIds.at(index);
}

GLuint MyMesh::getVertexBufferObjectId(int index){
	if(index < 0 || index >= this->vertexBufferObjectIds.size()){
		cout << "invalid position in vertexBufferObjectIds for index = " << index << endl;
		return 0;
	}
	return this->vertexBufferObjectIds.at(index);
}

GLuint MyMesh::getTextureId(int index){
	if(index < 0 || index >= this->textureIds.size()){
		cout << "invalid position in textureIds for index = " << index << endl;
		return 0;
	}
	return this->textureIds.at(index);
}

GLint MyMesh::getAttributeId(int index){
	if(index < 0 || index >= this->attributesIds.size()){
		cout << "invalid position in attibutesIds for index = " << index << endl;
		return -1;
	}
	return this->attributesIds.at(index);
}

GLint MyMesh::getUniformId(int index){
	if(index < 0 || index >= this->uniformIds.size()){
		cout << "invalid position in uniformIds for index = " << index << endl;
		return -1;
	}
	return this->uniformIds.at(index);
}

char* MyMesh::getShaderFileName(int index){
	if(index < 0 || index >= this->shaderFilesName.size()){
		cout << "invalid position in shaderFilesName for index = " << index << endl;
		return "-1";
	}
	return this->shaderFilesName.at(index);
}

GLuint MyMesh::getProgramId(int index){
	if(index < 0 || index >= this->programsIds.size()){
		cout << "invalid position in programsIds for index = " << index << endl;
		return -1;
	}
	return this->programsIds.at(index);
}

std::vector<GLuint> MyMesh::getProgramsIds(){
	return this->programsIds;
}

//generate VAO ids based on numberIds
void MyMesh::generateVAOIds(int numberIds){
	GLuint aux[numberIds];
	
	if(numberIds >= 1){ 
		glGenVertexArrays(numberIds, aux);
		for(int i=0;i < numberIds;i++){
			this->vertexArrayObjectIds.push_back(aux[i]);
		}
	}
	
}

//generate VBO ids based on numberIds
void MyMesh::generateVBOIds(int numberIds){
	GLuint aux[numberIds];
	
	if(numberIds >= 1){ 
		glGenBuffers(numberIds, aux);
		for(int i=0;i < numberIds;i++){
			this->vertexBufferObjectIds.push_back(aux[i]);
		}
	}
	

}

//generate textures ids based on numberIds
void MyMesh::generateTextureIds(int numberIds){
	GLuint aux[numberIds];
	
	if( (numberIds >= 1) ){
		glGenTextures(numberIds, aux);
		for(int i=0;i < numberIds;i++){
			this->textureIds.push_back(aux[i]);
		}
	 }
}

//generate a texture id using the library SOIL
void MyMesh::generateTextureIdUsingSOIL(const char *filename, int force_channels, unsigned int reuse_texture_ID, unsigned int flags){
		//glActiveTexture(GL_TEXTURE0);
		
		this->textureIds.push_back(SOIL_load_OGL_texture (filename, force_channels,reuse_texture_ID, flags));
		this->textureFilesName.push_back(filename);
		if (textureIds.back() == 0){
			cout << "SOIL loading error: " << SOIL_last_result() << "(" << filename << ")" << endl;
		}
    	
}

//Get the attribute id based on a program  Id and the attribute name.
//The id is stored in the vector attributesIds
void MyMesh::generateAttributeId(GLuint programID, const char* attributeName){
	this->attributesIds.push_back(glGetAttribLocation(programID, attributeName));
	if(this->attributesIds.back() == -1){
		cout << "Could not bind attibute " << attributeName << endl;
	}
	
}

//Get the Uniform id based on a program  Id and the Uniform name.
//The id is stored in the vector uniformIds
void MyMesh::generateUniformId(GLuint programID, const char* uniformeName){
	this->uniformIds.push_back(glGetUniformLocation(programID, uniformeName));
	if(this->uniformIds.back() == -1){
		cout << "Could not bind Uniform " << uniformeName << endl;
	}
}

//Create a program id given a vertex and fragment shader file name.
//The Id is store in the vector programsIds
void MyMesh::createProgramId (const char* vertexShaderFileName, const char* fragmentShaderFileName ){
	this->programsIds.push_back(InitShader(vertexShaderFileName, fragmentShaderFileName));
}

//Put the number -1 in the vector textureIds.
//numberIds defines the limit the textureIds size
void MyMesh::generateNullTextureIds(int numberIds){
	
	if( (numberIds >= 1) ){
		for(int i=0;i < numberIds;i++){
			this->textureIds.push_back(-1);
		}
	 }
}

Reader MyMesh::getReader(){
	return this->reader;
}

//add a vectice Coordinate in the vector vertices
void MyMesh::addVertice(glm::vec3 verticeCoordenates){
	this->vertices.push_back(glm::vec4(verticeCoordenates.x,verticeCoordenates.y,verticeCoordenates.z,1.0));
}

