#include "Spheres.h"

//constructor
Spheres::Spheres(float radius, int slices, int stacks){
	
	for (float theta = -M_PI / 2; theta < M_PI / 2 - 0.0001; theta += M_PI / stacks) {
		for (float phi = -M_PI; phi <= M_PI + 0.0001; phi += 2 * M_PI / slices) {
			this->mesh.addVertice(glm::vec3(  radius*(cos(theta) * sin(phi)), -sin(theta)*radius, radius*cos(theta) * cos(phi)   ));
			this->mesh.addVertice(glm::vec3(  radius*(cos(theta + M_PI / stacks) * sin(phi)), -sin(theta + M_PI / stacks)*radius, radius*cos(theta + M_PI / stacks) * cos(phi)));
			
			this->mesh.addNormal(glm::vec3(  radius*(cos(theta) * sin(phi)), -sin(theta)*radius, radius*cos(theta) * cos(phi)   ));
			this->mesh.addNormal(glm::vec3(  radius*(cos(theta + M_PI / stacks) * sin(phi)), -sin(theta + M_PI / stacks)*radius, radius*cos(theta + M_PI / stacks) * cos(phi)));			
		}
		
	}
	
	position = glm::vec3(0.0,10.0,0.0);
	scale = 1;
	anglePath = 0.0;
	
}


//store the data in graphics cards and get attribute and uniform IDs
void Spheres::initSpheres(char* fileName, const char* vFile, const char* fFile){
	
	this->mesh.generateVAOIds(1);
	this->mesh.generateVBOIds(2);
	
	glBindVertexArray(this->mesh.getVertexArrayObjectId(0));
	glBindBuffer(GL_ARRAY_BUFFER,this->mesh.getVertexBufferObjectId(0));
	glBufferData(GL_ARRAY_BUFFER, this->mesh.getVectorVertices().size()*sizeof(this->mesh.getVertice(0)), this->mesh.getVectorVertices().data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER,this->mesh.getVertexBufferObjectId(1));
	glBufferData(GL_ARRAY_BUFFER, this->mesh.getVectorNormals().size()*sizeof(this->mesh.getNormal(0)), this->mesh.getVectorNormals().data(), GL_STATIC_DRAW);

	
	this->mesh.generateTextureIdUsingSOIL(fileName,SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS);
	this->mesh.generateTextureIdUsingSOIL("external_files/tutes/Land_shallow_topo_2048.jpg",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS);
	
	this->mesh.createProgramId(vFile,fFile);
	glUseProgram(this->mesh.getProgramId(0));
	
	this->mesh.generateAttributeId(this->mesh.getProgramId(0),"v_coord");
	this->mesh.generateAttributeId(this->mesh.getProgramId(0),"v_coord");
	
	this->mesh.generateUniformId(this->mesh.getProgramId(0), "m");//0
	this->mesh.generateUniformId(this->mesh.getProgramId(0), "v");//1
	this->mesh.generateUniformId(this->mesh.getProgramId(0), "p");//2
	this->mesh.generateUniformId(this->mesh.getProgramId(0), "m_3x3_inv_transp");//3
	this->mesh.generateUniformId(this->mesh.getProgramId(0), "v_inv");//4
	this->mesh.generateUniformId(this->mesh.getProgramId(0), "mytexture");//5
	this->mesh.generateUniformId(this->mesh.getProgramId(0), "alpha");//6
	this->mesh.generateUniformId(this->mesh.getProgramId(0), "overrideColor");//7
	
	
}

//draw the spheres
void Spheres::draw(glm::mat4 view,glm::mat4 projection, glm::vec3 scale, glm::vec3 color){
	glUseProgram(this->mesh.getProgramId(0));
	glBindVertexArray(this->mesh.getVertexArrayObjectId(0));
	
	float R1 = 18;
	float R2 = 12;
	float R3 = 6;
	float R4 = 0;
	
	const GLfloat alpha = 0.7;
	

	anglePath += 0.01;
	if(anglePath >= 2*M_PI){
			anglePath = 0;
	}
	
	position.x = R1*cos(anglePath);
	position.z = R1*sin(anglePath);
	
	float angle = glutGet(GLUT_ELAPSED_TIME) / 1000.0 * 30;  // 30° per second
	glm::mat4 anim = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0));
	glm::mat4 fix_orientation = glm::rotate(glm::mat4(1.0f), -90.f, glm::vec3(1, 0, 0));
	glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 m = model * anim * fix_orientation;
	m = glm::scale(m,glm::vec3(0.5,0.5,0.5)*scale);
	glm::mat3 m_3x3_inv_transp = glm::transpose(glm::inverse(glm::mat3(m)));
	glm::mat4 v_inv = glm::inverse(view);
	

	
	glUniformMatrix4fv(this->mesh.getUniformId(0), 1, GL_FALSE, glm::value_ptr(m));
	glUniformMatrix4fv(this->mesh.getUniformId(1), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(this->mesh.getUniformId(2), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix3fv(this->mesh.getUniformId(3), 1, GL_FALSE, glm::value_ptr(m_3x3_inv_transp));
	glUniformMatrix4fv(this->mesh.getUniformId(4), 1, GL_FALSE, glm::value_ptr(v_inv));
	glUniform1fv(this->mesh.getUniformId(6),  1, &alpha);
	glUniform3f(this->mesh.getUniformId(7), color.x, color.y, color.z);
	
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->mesh.getTextureId(0));
	glUniform1i(this->mesh.getUniformId(5), /*GL_TEXTURE*/0);

	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, this->mesh.getTextureId(1));
	//glUniform1i(this->mesh.getUniformId(6), /*GL_TEXTURE*/1);


	glEnableVertexAttribArray(this->mesh.getAttributeId(0));
	glBindBuffer(GL_ARRAY_BUFFER, this->mesh.getVertexBufferObjectId(0));
	glVertexAttribPointer(this->mesh.getAttributeId(0), 4, GL_FLOAT, GL_FALSE, 0, 0);
	
	glEnableVertexAttribArray(this->mesh.getAttributeId(1));
	glBindBuffer(GL_ARRAY_BUFFER, this->mesh.getVertexBufferObjectId(1));
	glVertexAttribPointer(this->mesh.getAttributeId(1), 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->mesh.getVectorVertices().size());
	glCullFace(GL_BACK);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->mesh.getVectorVertices().size());
	glDisable(GL_CULL_FACE);


	position.x = R2*cos(anglePath);
	position.z = R2*sin(anglePath);
	
	
	model = glm::translate(glm::mat4(1.0f), position);
	m = model * anim * fix_orientation;
	m = glm::scale(m,glm::vec3(1,1,1)*scale);
	
	m_3x3_inv_transp = glm::transpose(glm::inverse(glm::mat3(m)));
	
	glUniformMatrix4fv(this->mesh.getUniformId(0), 1, GL_FALSE, glm::value_ptr(m));
	glUniformMatrix3fv(this->mesh.getUniformId(3), 1, GL_FALSE, glm::value_ptr(m_3x3_inv_transp));

	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->mesh.getVectorVertices().size());
	glCullFace(GL_BACK);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->mesh.getVectorVertices().size());
	glDisable(GL_CULL_FACE);
	
	position.x = R3*cos(anglePath);
	position.z = R3*sin(anglePath);
	
	
	model = glm::translate(glm::mat4(1.0f), position);
	m = model * anim * fix_orientation;
	m = glm::scale(m,glm::vec3(1.5,1.5,1.5)*scale);
	
	m_3x3_inv_transp = glm::transpose(glm::inverse(glm::mat3(m)));
	
	glUniformMatrix4fv(this->mesh.getUniformId(0), 1, GL_FALSE, glm::value_ptr(m));
	glUniformMatrix3fv(this->mesh.getUniformId(3), 1, GL_FALSE, glm::value_ptr(m_3x3_inv_transp));


	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->mesh.getVectorVertices().size());
	glCullFace(GL_BACK);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->mesh.getVectorVertices().size());
	glDisable(GL_CULL_FACE);
	
	position.x = R4*cos(anglePath);
	position.z = R4*sin(anglePath);
	
	
	model = glm::translate(glm::mat4(1.0f), position);
	m = model * anim * fix_orientation;
	m = glm::scale(m,glm::vec3(2.0,2.0,2.0)*scale);
	
	m_3x3_inv_transp = glm::transpose(glm::inverse(glm::mat3(m)));
	
	glUniformMatrix4fv(this->mesh.getUniformId(0), 1, GL_FALSE, glm::value_ptr(m));
	glUniformMatrix3fv(this->mesh.getUniformId(3), 1, GL_FALSE, glm::value_ptr(m_3x3_inv_transp));


	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->mesh.getVectorVertices().size());
	glCullFace(GL_BACK);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->mesh.getVectorVertices().size());
	glDisable(GL_CULL_FACE);
		
}





