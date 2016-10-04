#include "Soldier.h"

Soldier::Soldier(){
	this->position = glm::vec3(0.0);
}

MyMesh Soldier::getMesh(){
	return this->mesh;
}

glm::vec3 Soldier::getPosition(){
	return this->position;
}

void Soldier::setMesh(MyMesh _mesh){
	this->mesh = _mesh;
}

void Soldier::setPosition(glm::vec3 _position){
	this->position = _position;
	this->mesh.setModelMatrix(glm::translate(this->mesh.getModelMatrix(), _position));
}

//Store object vertices, normals and/or elements in graphic card buffers
void Soldier::InitSoldierUsingGlmModel(){
	//use MyMesh to read the .obj, textures and shaders files
	this->mesh.reader.init("external_files/Soldier/edf_soldier_a.obj","shaders/vl.glsl","shaders/fl.glsl");
	
}

void Soldier::draw(glm::mat4 model, glm::mat4 view,glm::mat4 projection, glm::vec3 scale, float alpha, glm::vec3 color){
	
	//GLfloat alpha = 1.0;//define alpha
		
	glBindVertexArray(this->mesh.reader.vao);
	glUseProgram(this->mesh.reader.program);
	
	//store data inside the graphics card
	glEnableVertexAttribArray(this->mesh.reader.attribute_coord3d);
	glBindBuffer(GL_ARRAY_BUFFER, this->mesh.reader.vbo_model_vertices);
	glVertexAttribPointer(this->mesh.reader.attribute_coord3d, 3, GL_FLOAT, GL_FALSE,0, 0);
	
	glEnableVertexAttribArray(this->mesh.reader.attribute_normal);
	glBindBuffer(GL_ARRAY_BUFFER, this->mesh.reader.vbo_model_normal);
	glVertexAttribPointer(this->mesh.reader.attribute_normal, 3, GL_FLOAT, GL_FALSE,0, 0);
	
	glEnableVertexAttribArray(this->mesh.reader.attribute_texcoord);
	glBindBuffer(GL_ARRAY_BUFFER, this->mesh.reader.vbo_model_texcoords);
	glVertexAttribPointer(this->mesh.reader.attribute_texcoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
	///////////////////
	
	model = glm::scale(model,scale);
	glm::mat3 m_3x3_inv_transp = glm::transpose(glm::inverse(glm::mat3(model)));
	glm::mat4 v_inv = glm::inverse(view);
	

	glUniformMatrix4fv(this->mesh.reader.uniform_m, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(this->mesh.reader.uniform_v, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(this->mesh.reader.uniform_projection, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(this->mesh.reader.uniform_m_3x3_inv_transp, 1, GL_FALSE, glm::value_ptr(m_3x3_inv_transp));
	glUniformMatrix4fv(this->mesh.reader.uniform_v_inv , 1, GL_FALSE, glm::value_ptr(v_inv ));
	glUniform1fv(this->mesh.reader.uniform_alpha , 1, &alpha);
	glUniform3f(this->mesh.reader.uniform_overrideColor, color.x, color.y, color.z);
	
	//I used the same code-block from the assignment 2 to draw
	
	glActiveTexture(GL_TEXTURE0);
	
	//loop through groups
	
	GLMgroup* group = this->mesh.reader.model_ptr->groups;
    
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
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mesh.reader.ibo_model_elements[current_group]);
  //how many elements in what we want to draw?? Sure, we could have kept this as state rather than enquiring now.....
  int size;  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

    //glUniform3fv(my_program.uniform_Kd,1,(const GLfloat *)  &(model_ptr->materials[group->material].diffuse));
	
	glBindTexture(GL_TEXTURE_2D, this->mesh.reader.model_texture_ids[current_group]);
	glUniform1i(this->mesh.reader.uniform_texture, /*GL_TEXTURE*/0); 

	glDrawElements(GL_TRIANGLES, size/sizeof(GLuint), GL_UNSIGNED_INT, 0);
        group=group->next;
        current_group++;
    }//end looping through groups
		
}



