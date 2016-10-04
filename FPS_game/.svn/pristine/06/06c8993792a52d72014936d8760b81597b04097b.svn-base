#include "Mirror.h"

Mirror::Mirror(){
	this->position = glm::vec3(0.0f);
}

void Mirror::generateMirror(){
	
	// bottom
	this->mesh.addVertice(glm::vec4(-1.0, 0.0, -1.0,  1.0));
	this->mesh.addVertice(glm::vec4( 1.0, 0.0, -1.0,  1.0));
	this->mesh.addVertice(glm::vec4( 1.0, 0.0,  1.0,  1.0));
	this->mesh.addVertice(glm::vec4(-1.0, 0.0,  1.0,  1.0));
	
	this->mesh.addTextureCoordenate(glm::vec2(0.0, 0.0));
	this->mesh.addTextureCoordenate(glm::vec2(1.0, 0.0));
	this->mesh.addTextureCoordenate(glm::vec2(1.0, 1.0));
	this->mesh.addTextureCoordenate(glm::vec2(0.0, 1.0));
	
	GLushort cube_elements[] = {
		// front
		0,  1,  2,
		2,  3,  0,
	};
	
	for (int i = 0; i < sizeof(cube_elements)/sizeof(cube_elements[0]); i++){
		this->mesh.addElement(cube_elements[i]);
	}
	
	for(int i=0;i<4;i++){this->mesh.addNormal(glm::vec3( 0.0,  -1.0,  0.0));}

	
}

void Mirror::loadMirror(char* textureFileName,const char* vertexShaderFileName, const char* FragmentShaderFileName ){
	
	this->mesh.generateVAOIds(1);
	this->mesh.generateVBOIds(4);
	
	glBindVertexArray(this->mesh.getVertexArrayObjectId(0));
	this->mesh.createProgramId(vertexShaderFileName,FragmentShaderFileName);
	glUseProgram(this->mesh.getProgramId(0));
	
	this->generateMirror();
	
	//glBindBuffer(GL_ARRAY_BUFFER, this->mesh.getVertexBufferObjectId(0));
	//glBufferData(GL_ARRAY_BUFFER, this->mesh.getVectorVertices().size()*sizeof(this->mesh.getVertice(0)) , this->mesh.getVectorVertices().data(), GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, this->mesh.getVertexBufferObjectId(1));
	//glBufferData(GL_ARRAY_BUFFER, this->mesh.getVectorVertices().size()*sizeof(this->mesh.getVertice(0)) , this->mesh.getVectorVertices().data(), GL_STATIC_DRAW);

	
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
	this->mesh.generateUniformId(this->mesh.getProgramId(0),"projection");//2

	this->mesh.generateUniformId(this->mesh.getProgramId(0),"mytexture");//3
	
	this->mesh.generateUniformId(this->mesh.getProgramId(0), "m_3x3_inv_transp");//4
	this->mesh.generateUniformId(this->mesh.getProgramId(0), "v_inv");//5
	this->mesh.generateUniformId(this->mesh.getProgramId(0), "alpha");//6
	this->mesh.generateUniformId(this->mesh.getProgramId(0), "overrideColor");//7
	
		
	this->mesh.generateTextureIdUsingSOIL(textureFileName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS);
	
}

void Mirror::draw(glm::mat4 view,glm::mat4 projection, glm::vec3 scale, GLfloat alpha, glm::vec3 color){
	
	
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
        3,                  // number of elements per vertex, here (x,y,z,w)
        GL_FLOAT,           // the type of each element
        GL_FALSE,           // take our values as-is
        0,                  // no extra data between each position
        0                   // offset of first element
    );
    
    glEnableVertexAttribArray(this->mesh.getAttributeId(2));
    glBindBuffer(GL_ARRAY_BUFFER, this->mesh.getVertexBufferObjectId(3));
    glVertexAttribPointer(
        this->mesh.getAttributeId(2),  // attribute
        2,                  // number of elements per vertex, here (x,y,z,w)
        GL_FLOAT,           // the type of each element
        GL_FALSE,           // take our values as-is
        0,                  // no extra data between each position
        0                   // offset of first element
    ); 
    
    this->logic(view,projection,scale, alpha, color); 
	
	
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->mesh.getTextureId(0));
	glUniform1i(this->mesh.getUniformId(3), /*GL_TEXTURE*/0);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mesh.getVertexBufferObjectId(2));
	
	int size;  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	
	glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	
	
}

void Mirror::logic(glm::mat4 view,glm::mat4 projection, glm::vec3 scale, GLfloat alpha, glm::vec3 color){
	
	
	glm::vec3 object_position = glm::vec3(0.0, 0.0, 0.0);
	this->mesh.setModelMatrix(glm::translate(glm::mat4(1.0f), this->position)) ;
	this->mesh.setModelMatrix(glm::scale(this->mesh.getModelMatrix(),glm::vec3(20,20,20)*scale)); 
	glm::mat3 m_3x3_inv_transp = glm::transpose(glm::inverse(glm::mat3(this->mesh.getModelMatrix())));
	glm::mat4 v_inv = glm::inverse(view);
	//model = model* anim;
	//glUseProgram(this->mesh.getProgramId(0));
	
  
	glUniformMatrix4fv(this->mesh.getUniformId(0), 1, GL_FALSE, glm::value_ptr(this->mesh.getModelMatrix()));
	glUniformMatrix4fv(this->mesh.getUniformId(1), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(this->mesh.getUniformId(2), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(this->mesh.getUniformId(4), 1, GL_FALSE, glm::value_ptr(m_3x3_inv_transp));
	glUniformMatrix4fv(this->mesh.getUniformId(5), 1, GL_FALSE, glm::value_ptr(v_inv));
	glUniform1fv(this->mesh.getUniformId(6), 1, &alpha);
	glUniform3f(this->mesh.getUniformId(7), color.x, color.y, color.z);
	
}

