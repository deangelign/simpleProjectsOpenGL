#include "SkyBox.h"

SkyBox::SkyBox(){
	this->position = glm::vec3(0.0);
}

MyMesh SkyBox::getMesh(){
	return this->mesh;
}

glm::vec3 SkyBox::getPosition(){
	return this->position;
}

void SkyBox::setMesh(MyMesh _mesh){
	this->mesh = _mesh;
}

void SkyBox::setPosition(glm::vec3 _position){
	this->position = _position;
	this->mesh.setModelMatrix(glm::translate(this->mesh.getModelMatrix(), _position));
}


//generate Cube vertices, normals, textures coordinates and the elements
void SkyBox::generateCube(){
	 // front
	this->mesh.addVertice(glm::vec4(-1.0, 0.0,  1.0,  1.0));
	this->mesh.addVertice(glm::vec4( 1.0, 0.0,  1.0,  1.0));
	this->mesh.addVertice(glm::vec4( 1.0,  1.0,  1.0,  1.0));
	this->mesh.addVertice(glm::vec4(-1.0,  1.0,  1.0,  1.0));
	
	this->mesh.addTextureCoordenate(glm::vec2(0.0, 0.0));
	this->mesh.addTextureCoordenate(glm::vec2(1.0, 0.0));
	this->mesh.addTextureCoordenate(glm::vec2(1.0, 1.0));
	this->mesh.addTextureCoordenate(glm::vec2(0.0, 1.0));
	
	// top
	this->mesh.addVertice(glm::vec4(-1.0,  1.0,  1.0,  1.0));
	this->mesh.addVertice(glm::vec4( 1.0,  1.0,  1.0,  1.0));
	this->mesh.addVertice(glm::vec4( 1.0,  1.0, -1.0,  1.0));
	this->mesh.addVertice(glm::vec4(-1.0,  1.0, -1.0,  1.0));
	
	this->mesh.addTextureCoordenate(glm::vec2(0.0, 0.0));
	this->mesh.addTextureCoordenate(glm::vec2(1.0, 0.0));
	this->mesh.addTextureCoordenate(glm::vec2(1.0, 1.0));
	this->mesh.addTextureCoordenate(glm::vec2(0.0, 1.0));
	
	// back
	this->mesh.addVertice(glm::vec4( 1.0, 0.0, -1.0,  1.0));
	this->mesh.addVertice(glm::vec4(-1.0, 0.0, -1.0,  1.0));
	this->mesh.addVertice(glm::vec4(-1.0,  1.0, -1.0,  1.0));
	this->mesh.addVertice(glm::vec4( 1.0,  1.0, -1.0,  1.0));
	
	this->mesh.addTextureCoordenate(glm::vec2(0.0, 0.0));
	this->mesh.addTextureCoordenate(glm::vec2(1.0, 0.0));
	this->mesh.addTextureCoordenate(glm::vec2(1.0, 1.0));
	this->mesh.addTextureCoordenate(glm::vec2(0.0, 1.0));
	
	// left
	this->mesh.addVertice(glm::vec4(-1.0, 0.0, -1.0,  1.0));
	this->mesh.addVertice(glm::vec4(-1.0, 0.0,  1.0,  1.0));
	this->mesh.addVertice(glm::vec4(-1.0,  1.0,  1.0,  1.0));
	this->mesh.addVertice(glm::vec4(-1.0,  1.0, -1.0,  1.0));
	
	this->mesh.addTextureCoordenate(glm::vec2(0.0, 0.0));
	this->mesh.addTextureCoordenate(glm::vec2(1.0, 0.0));
	this->mesh.addTextureCoordenate(glm::vec2(1.0, 1.0));
	this->mesh.addTextureCoordenate(glm::vec2(0.0, 1.0));
	
	// right
	this->mesh.addVertice(glm::vec4( 1.0, 0.0,  1.0,  1.0));
	this->mesh.addVertice(glm::vec4( 1.0, 0.0, -1.0,  1.0));
	this->mesh.addVertice(glm::vec4( 1.0,  1.0, -1.0,  1.0));
	this->mesh.addVertice(glm::vec4( 1.0,  1.0,  1.0,  1.0));
	
	this->mesh.addTextureCoordenate(glm::vec2(0.0, 0.0));
	this->mesh.addTextureCoordenate(glm::vec2(1.0, 0.0));
	this->mesh.addTextureCoordenate(glm::vec2(1.0, 1.0));
	this->mesh.addTextureCoordenate(glm::vec2(0.0, 1.0));

	for(int i=0;i<4;i++){this->mesh.addNormal(glm::vec3( 0.0,  0.0,  1.0));}
	for(int i=0;i<4;i++){this->mesh.addNormal(glm::vec3( 0.0,  1.0,  0.0));}
	for(int i=0;i<4;i++){this->mesh.addNormal(glm::vec3( 0.0,  0.0,  -1.0));}
	for(int i=0;i<4;i++){this->mesh.addNormal(glm::vec3( -1.0,  0.0,  0.0));}
	for(int i=0;i<4;i++){this->mesh.addNormal(glm::vec3( 1.0,  0.0,  0.0));}

	GLushort cube_elements[] = {
		// front
		0,  1,  2,
		2,  3,  0,
		
		// back
		8,  9, 10,
		10, 11,  8,
		// left
		12, 13, 14,
		14, 15, 12,
		// right
		16, 17, 18,
		18, 19, 16,

		// top
		4,  5,  6,
		6,  7,  4,
	};

	for (int i = 0; i < sizeof(cube_elements)/sizeof(cube_elements[0]); i++){
		this->mesh.addElement(cube_elements[i]);
	}

	

	
}


//store the data in the graphics cards and generate the textures ids based on 
//input parameters
void SkyBox::loadSkyBox(char* _frontTextureFileName, char* _backTextureFileName,char* _leftTextureFileName,char* _rightTextureFileName,char* _topTextureFileName){
	
	this->mesh.generateVAOIds(1);
	this->mesh.generateVBOIds(4);
	
	glBindVertexArray(this->mesh.getVertexArrayObjectId(0));
	this->mesh.createProgramId("shaders/vlSkyBox.glsl","shaders/flSkyBox.glsl");
	glUseProgram(this->mesh.getProgramId(0));
	
	this->generateCube();
	
	this->mesh.storeDataInBuffer(this->mesh.getVertexArrayObjectId(0),this->mesh.getVertexBufferObjectId(0),GL_ARRAY_BUFFER, this->mesh.getVectorVertices().size()*sizeof(this->mesh.getVertice(0)), this->mesh.getVectorVertices().data(),GL_STATIC_DRAW  );
	this->mesh.storeDataInBuffer(this->mesh.getVertexArrayObjectId(0),this->mesh.getVertexBufferObjectId(1),GL_ARRAY_BUFFER, this->mesh.getVectorNormals().size()*sizeof(this->mesh.getNormal(0)), this->mesh.getVectorNormals().data(),GL_STATIC_DRAW  );
	this->mesh.storeDataInBuffer(this->mesh.getVertexArrayObjectId(0),this->mesh.getVertexBufferObjectId(2),GL_ELEMENT_ARRAY_BUFFER, (this->mesh.getVectorElements().size())*sizeof(this->mesh.getElement(0)), this->mesh.getVectorElements().data(),GL_STATIC_DRAW  );
	this->mesh.storeDataInBuffer(this->mesh.getVertexArrayObjectId(0),this->mesh.getVertexBufferObjectId(3),GL_ARRAY_BUFFER, (this->mesh.getVectorTextureCoordenates().size())*sizeof(this->mesh.getTextureCoordenate(0)), this->mesh.getVectorTextureCoordenates().data(),GL_STATIC_DRAW  );
	
	glUseProgram(this->mesh.getProgramId(0));
	this->mesh.generateAttributeId(this->mesh.getProgramId(0),"v_coord");
	this->mesh.generateAttributeId(this->mesh.getProgramId(0),"v_normal");
	this->mesh.generateAttributeId(this->mesh.getProgramId(0),"v_textCoord");
	
	this->mesh.generateUniformId(this->mesh.getProgramId(0),"m");//0
	this->mesh.generateUniformId(this->mesh.getProgramId(0),"v");//1
	this->mesh.generateUniformId(this->mesh.getProgramId(0),"p");//2

	this->mesh.generateUniformId(this->mesh.getProgramId(0),"mytextureFront");//3
	this->mesh.generateUniformId(this->mesh.getProgramId(0),"mytextureTop");//4
	this->mesh.generateUniformId(this->mesh.getProgramId(0),"mytextureBack");//5
	this->mesh.generateUniformId(this->mesh.getProgramId(0),"mytextureRight");//6
	this->mesh.generateUniformId(this->mesh.getProgramId(0),"mytextureLeft");//7

	this->mesh.generateUniformId(this->mesh.getProgramId(0), "m_3x3_inv_transp");//8
	this->mesh.generateUniformId(this->mesh.getProgramId(0), "v_inv");//9
	this->mesh.generateUniformId(this->mesh.getProgramId(0), "alpha");//10
	
	
	//generating textures IDS
	this->mesh.generateTextureIdUsingSOIL(_frontTextureFileName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS);
	this->mesh.generateTextureIdUsingSOIL(_topTextureFileName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS);
	this->mesh.generateTextureIdUsingSOIL(_backTextureFileName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS);
	this->mesh.generateTextureIdUsingSOIL(_leftTextureFileName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS);
	this->mesh.generateTextureIdUsingSOIL(_rightTextureFileName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS);
	
	this->mesh.addTextureFilesName(_frontTextureFileName);
	this->mesh.addTextureFilesName(_topTextureFileName);
	this->mesh.addTextureFilesName(_backTextureFileName);
	this->mesh.addTextureFilesName(_leftTextureFileName);
	this->mesh.addTextureFilesName(_rightTextureFileName);
	
	


}

//send the information to the graphics cards, compute the required matrices and draw
void SkyBox::draw(glm::mat4 view,glm::mat4 projection, glm::vec3 scale,int cameraIndex){
	
	glBindVertexArray(this->mesh.getVertexArrayObjectId(0));
	glUseProgram(this->mesh.getProgramId(0));
	
    
	glEnableVertexAttribArray(this->mesh.getAttributeId(0));
	glBindBuffer(GL_ARRAY_BUFFER, this->mesh.getVertexBufferObjectId(0));
	glVertexAttribPointer(
        this->mesh.getAttributeId(0),  // attribute
        4,                  // number of elements per vertex, here (x,y,z,w)
        GL_FLOAT,           // the type of each element
        GL_FALSE,           // take our values as-is
        0,                  // no extra data between each position
        0                   // offset of first element
    );
    glEnableVertexAttribArray(this->mesh.getAttributeId(1));
    glBindBuffer(GL_ARRAY_BUFFER, this->mesh.getVertexBufferObjectId(1));
    glVertexAttribPointer(
        this->mesh.getAttributeId(1),  // attribute
        3,                  // number of elements per vertex, here (x,y,z)
        GL_FLOAT,           // the type of each element
        GL_FALSE,           // take our values as-is
        0,                  // no extra data between each position
        0                   // offset of first element
    );
    
    glEnableVertexAttribArray(this->mesh.getAttributeId(2));
    glBindBuffer(GL_ARRAY_BUFFER, this->mesh.getVertexBufferObjectId(3));
    glVertexAttribPointer(
        this->mesh.getAttributeId(2),  // attribute
        2,                  // number of elements per vertex, here (x,y)
        GL_FLOAT,           // the type of each element
        GL_FALSE,           // take our values as-is
        0,                  // no extra data between each position
        0                   // offset of first element
    );  
  
   this->logic(view,projection, scale);   

	
	glBindVertexArray(this->mesh.getVertexArrayObjectId(0));
	glUseProgram(this->mesh.getProgramId(0));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->mesh.getTextureId(0));
	glUniform1i(this->mesh.getUniformId(3), /*GL_TEXTURE*/0);
	
	
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->mesh.getTextureId(1));
	glUniform1i(this->mesh.getUniformId(4), /*GL_TEXTURE*/1);
	
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, this->mesh.getTextureId(2));
	glUniform1i(this->mesh.getUniformId(5), /*GL_TEXTURE*/2);
	
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, this->mesh.getTextureId(3));
	glUniform1i(this->mesh.getUniformId(6), /*GL_TEXTURE*/3);
	
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, this->mesh.getTextureId(4));
	glUniform1i(this->mesh.getUniformId(7), /*GL_TEXTURE*/4);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mesh.getVertexBufferObjectId(2));
	int size;  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	
	if(cameraIndex == 0 || cameraIndex == 2){
		glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);//normal camera
	}
	
	if(cameraIndex == 1){
		glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_SHORT, 0);//sky-view
	}
}

//this method just compute the mrequired matrices
//and send the information to the graphics cards
void SkyBox::logic(glm::mat4 view,glm::mat4 projection,glm::vec3 scale){
	
	GLfloat alpha = 1.0;
	
	glm::vec3 object_position = glm::vec3(0.0, 0.0, 0.0);
	this->mesh.setModelMatrix(glm::translate(glm::mat4(1.0f), this->position)) ;
	this->mesh.setModelMatrix(glm::scale(this->mesh.getModelMatrix(),scale)); 
	glm::mat3 m_3x3_inv_transp = glm::transpose(glm::inverse(glm::mat3(this->mesh.getModelMatrix())));
	glm::mat4 v_inv = glm::inverse(view);
	
  
	glUniformMatrix4fv(this->mesh.getUniformId(0), 1, GL_FALSE, glm::value_ptr(this->mesh.getModelMatrix()));
	glUniformMatrix4fv(this->mesh.getUniformId(1), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(this->mesh.getUniformId(2), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(this->mesh.getUniformId(8), 1, GL_FALSE, glm::value_ptr(m_3x3_inv_transp));
	glUniformMatrix4fv(this->mesh.getUniformId(9), 1, GL_FALSE, glm::value_ptr(v_inv));
	glUniform1fv(this->mesh.getUniformId(10), 1, &alpha);

	
}


