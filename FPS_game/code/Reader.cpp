#include "Reader.h"

//the purpose of this class is only read .obj and store their information
//in local variable

//default constructor
Reader::Reader(){
		
}

//read a object file (.obj), a vertex shader file and a fragment shader file,
//and store all the information in local variables
void Reader::init(char* fileName,const char* vertexShaderFileName,const char* fragmentShaderFileName){
	
	glGenVertexArrays( 1, &vao );
	glBindVertexArray(vao);
	program = InitShader(vertexShaderFileName,fragmentShaderFileName);
	glUseProgram(program);
	
	 
	model_ptr = myReadObj(fileName);
	
	storeData();
	
	
	glGenBuffers(1, &(vbo_model_vertices));
	glBindBuffer(GL_ARRAY_BUFFER, vbo_model_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(*(vpositions))*(model_ptr->numtriangles)*3*3, vpositions, GL_STATIC_DRAW);
	
	glGenBuffers(1, &(vbo_model_normal));
	glBindBuffer(GL_ARRAY_BUFFER, vbo_model_normal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(*(vpositions))*(model_ptr->numtriangles)*3*3, vNormal, GL_STATIC_DRAW);
	  
	glGenBuffers(1, &(vbo_model_texcoords));
	glBindBuffer(GL_ARRAY_BUFFER, vbo_model_texcoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(*(tcoords))*(model_ptr->numtriangles)*3*2, tcoords, GL_STATIC_DRAW);
	
	ibo_model_elements= (GLuint *) malloc(sizeof(GLuint)*model_ptr->numgroups);
	glGenBuffers(model_ptr->numgroups, ibo_model_elements);
	ibo_model_buffer= (GLuint **) malloc(sizeof(GLuint *)*model_ptr->numgroups);
	  
	model_texture_ids= (GLuint *) malloc(sizeof(GLuint)*model_ptr->numgroups);  
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

				model_texture_ids[current_group]= SOIL_load_OGL_texture
				(
					model_ptr->materials[group->material].map_Kd_file,
					SOIL_LOAD_AUTO,
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
				);
				if (model_texture_ids[current_group])
				std::cerr << " loaded texture " << model_ptr->materials[group->material].map_Kd_file << "ok" << std::endl;
				else
				std::cerr << " failed to load texture " << model_ptr->materials[group->material].map_Kd_file << std::endl;
		   }
		} //end group not empty
		
	//now the data for a group is actually an index into a triangle which is then something that gives three indices into our vertex array. 

		ibo_model_buffer[current_group] = (GLuint *) malloc(sizeof(GLuint)*3*(group->numtriangles));
		for (int i=0;i<(group->numtriangles);i++)
		{
			ibo_model_buffer[current_group][3*i+0]=group->triangles[i]*3+0;
			ibo_model_buffer[current_group][3*i+1]=group->triangles[i]*3+1;
			ibo_model_buffer[current_group][3*i+2]=group->triangles[i]*3+2;
		}
		//now we say we will refer to this buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_model_elements[current_group]);
		//for this buffer we say what the buffer looks like and where it lives
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*3*(group->numtriangles), ibo_model_buffer[current_group], GL_STATIC_DRAW);

		group=group->next;
		current_group++;
	} //end looping over groups
	
	glUseProgram(program);
	
	getAttiributeAndUniformIDs();
}

void Reader::storeData(){
	
	vpositions=  (GLfloat *) malloc(sizeof(GLfloat)*model_ptr->numtriangles*3*3);
	vNormal = (GLfloat *)malloc(sizeof(GLfloat)*model_ptr->numtriangles*3*3);
	tcoords=  (GLfloat *) malloc(sizeof(GLfloat)*model_ptr->numtriangles*3*2);
	
	//cout << model_ptr->triangles[i].tindices[0] << endl;
	
	
	
	
	for (int i=0;i<model_ptr->numtriangles;i++)
   {
	  
     tcoords[i*2*3+0]=model_ptr->texcoords[model_ptr->triangles[i].tindices[0]*2+0];
     tcoords[i*2*3+1]=model_ptr->texcoords[model_ptr->triangles[i].tindices[0]*2+1];

     tcoords[i*2*3+2]=model_ptr->texcoords[model_ptr->triangles[i].tindices[1]*2+0];
     tcoords[i*2*3+3]=model_ptr->texcoords[model_ptr->triangles[i].tindices[1]*2+1];

     tcoords[i*2*3+4]=model_ptr->texcoords[model_ptr->triangles[i].tindices[2]*2+0];
     tcoords[i*2*3+5]=model_ptr->texcoords[model_ptr->triangles[i].tindices[2]*2+1];

     vpositions[i*3*3+0]=model_ptr->vertices[model_ptr->triangles[i].vindices[0]*3+0];
     vpositions[i*3*3+1]=model_ptr->vertices[model_ptr->triangles[i].vindices[0]*3+1];
     vpositions[i*3*3+2]=model_ptr->vertices[model_ptr->triangles[i].vindices[0]*3+2];

     vpositions[i*3*3+3]=model_ptr->vertices[model_ptr->triangles[i].vindices[1]*3+0];
     vpositions[i*3*3+4]=model_ptr->vertices[model_ptr->triangles[i].vindices[1]*3+1];
     vpositions[i*3*3+5]=model_ptr->vertices[model_ptr->triangles[i].vindices[1]*3+2];

     vpositions[i*3*3+6]=model_ptr->vertices[model_ptr->triangles[i].vindices[2]*3+0];
     vpositions[i*3*3+7]=model_ptr->vertices[model_ptr->triangles[i].vindices[2]*3+1];
     vpositions[i*3*3+8]=model_ptr->vertices[model_ptr->triangles[i].vindices[2]*3+2];
	 
	 //I dont know why the number of the normals is not equal to the number of the vertices
	 //for this reason I decided calculate the normals by myself; 
	 
	 glm::vec3 pointA = glm::vec3(vpositions[i*3*3+0],vpositions[i*3*3+1],vpositions[i*3*3+2]);
	 glm::vec3 pointB = glm::vec3(vpositions[i*3*3+3],vpositions[i*3*3+4],vpositions[i*3*3+5]);
	 glm::vec3 pointC = glm::vec3(vpositions[i*3*3+6],vpositions[i*3*3+7],vpositions[i*3*3+8]);
	 
	 glm::vec3 vecAB = pointB - pointA;
	 glm::vec3 vecAC = pointC - pointA;
	 
	 glm::vec3 n = glm::vec3( (vecAB.y*vecAC.z - vecAB.z*vecAC.y),(vecAB.z*vecAC.x - vecAB.x*vecAC.z),(vecAB.x*vecAC.y - vecAB.y*vecAC.x));
	 vNormal[i*3*3+0] = n.x;
	 vNormal[i*3*3+1] = n.y;
	 vNormal[i*3*3+2] = n.z;
	 
	 vNormal[i*3*3+3] = n.x;
	 vNormal[i*3*3+4] = n.y;
	 vNormal[i*3*3+5] = n.z;
	 
	 vNormal[i*3*3+6] = n.x;
	 vNormal[i*3*3+7] = n.y;
	 vNormal[i*3*3+8] = n.z;
	 
   }

	
}


int Reader::getAttiributeAndUniformIDs(){
	const char* attribute_name;
	attribute_name = "v_coord";
	attribute_coord3d = glGetAttribLocation(program, attribute_name);
	if (attribute_coord3d == -1) {
		cerr << "Could not bind attribute " << attribute_name << endl;
		return 0;
	}
	attribute_name = "v_normal";
	attribute_normal = glGetAttribLocation(program, attribute_name);
	if (attribute_texcoord == -1) {
		cerr << "Could not bind attribute " << attribute_name << endl;
		return 0;
	}
	
	attribute_name = "v_textCoord";
	attribute_texcoord = glGetAttribLocation(program, attribute_name);
	if (attribute_texcoord == -1) {
		cerr << "Could not bind attribute " << attribute_name << endl;
		return 0;
	}
	
	const char* uniform_name;
	uniform_name = "m";
	uniform_m = glGetUniformLocation(program, uniform_name);
	if (uniform_m == -1) {
		cerr << "Could not bind uniform " <<  uniform_name << endl;
		return 0;
	}
	
	
	uniform_name = "v";
	uniform_v = glGetUniformLocation(program, uniform_name);
	if (uniform_v == -1) {
		cerr << "Could not bind uniform " <<  uniform_name << endl;
		return 0;
	}

	uniform_name = "projection";
	uniform_projection = glGetUniformLocation(program, uniform_name);
	if (uniform_projection == -1) {
		cerr << "Could not bind uniform " <<  uniform_name << endl;
		return 0;
	}


	uniform_name = "m_3x3_inv_transp";
	uniform_m_3x3_inv_transp = glGetUniformLocation(program, uniform_name);
	if (uniform_m_3x3_inv_transp == -1) {
		cerr << "Could not bind uniform " <<  uniform_name << endl;
		//return 0;
	}
	
	uniform_name = "mytexture";
	uniform_texture = glGetUniformLocation(program, uniform_name);
	if (uniform_texture == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
		//return 0;
	}
	
	uniform_name = "v_inv";
	uniform_v_inv = glGetUniformLocation(program, uniform_name);
	if (uniform_v_inv == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
		//return 0;
	}
	
	uniform_name = "alpha";
	uniform_alpha = glGetUniformLocation(program, uniform_name);
	if (uniform_v_inv == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
		//return 0;
	}
	
	uniform_name = "overrideColor";
	uniform_overrideColor = glGetUniformLocation(program, uniform_name);
	if (uniform_overrideColor == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
		//return 0;
	}

	
	return 1;
}

//Read a .obj file and store all information in a instance of GLMmodel 
 GLMmodel* Reader::myReadObj(char* fileName){
	GLMmodel* obj;
	obj = glmReadOBJ(fileName);
	glmUnitize(obj);
	
	glmFacetNormals(obj);
    glmVertexNormals(obj, 90.0);
	return obj;
}


//just used to debug the program
void Reader::draw(glm::mat4 view, glm::mat4 projection){
	
	glBindVertexArray(vao);
	glUseProgram(program);
	
	glEnableVertexAttribArray(attribute_coord3d);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_model_vertices);
	glVertexAttribPointer(attribute_coord3d, 3, GL_FLOAT, GL_FALSE,0, 0);
	
	glEnableVertexAttribArray(attribute_texcoord);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_model_texcoords);
	glVertexAttribPointer(attribute_texcoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
	
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 1.0, 0.0));
	
	glUniformMatrix4fv(uniform_m, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(uniform_m, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, glm::value_ptr(projection));
	
	glActiveTexture(GL_TEXTURE0);
	
	//loop through groups
	
	GLMgroup* group = model_ptr->groups;
    
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
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_model_elements[current_group]);
  //how many elements in what we want to draw?? Sure, we could have kept this as state rather than enquiring now.....
  int size;  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

    //glUniform3fv(my_program.uniform_Kd,1,(const GLfloat *)  &(model_ptr->materials[group->material].diffuse));
	
	glBindTexture(GL_TEXTURE_2D, model_texture_ids[current_group]);
	glUniform1i(uniform_texture, /*GL_TEXTURE*/0); 

	glDrawElements(GL_TRIANGLES, size/sizeof(GLuint), GL_UNSIGNED_INT, 0);
        group=group->next;
        current_group++;
    }//end looping through groups
	
	
}
