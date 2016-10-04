#ifndef __MYMESH_H__
#define __MYMESH_H__


#include <vector>
#include "Reader.h"


class MyMesh{

private:

	std::vector<glm::vec4>vertices;
	std::vector<glm::vec3>normals;
	std::vector<glm::vec2>textureCoordenates;
	std::vector<glm::vec3>tangents;
	std::vector<GLushort>elements;

	std::vector<GLuint> vertexArrayObjectIds;
	std::vector<GLuint> vertexBufferObjectIds;
	std::vector<GLuint> textureIds;
	std::vector<GLint> attributesIds;
	std::vector<GLint> uniformIds;
	std::vector<GLuint> programsIds;
	std::vector<char*> shaderFilesName;
	std::vector<const char*> textureFilesName;
	
	glm::mat4 modelMatrix;
	GLint lastVAO_ID;
	char* modelFileName;
	
		
public:
	MyMesh();
	Reader reader;
	//getters
	glm::vec4 getVertice(int index);
	glm::vec3 getNormal(int index);
	glm::vec2 getTextureCoordenate(int index);
	glm::vec3 getTangents(int index);
	GLushort getElement(int index);
	Reader getReader();
	
	vector<glm::vec4> getVectorVertices();
	vector<glm::vec3> getVectorNormals();
	vector<glm::vec2> getVectorTextureCoordenates();
	vector<glm::vec3> getVectorTangents();
	vector<GLushort> getVectorElements();
	
	GLuint getVertexArrayObjectId(int index);
	GLuint getVertexBufferObjectId(int index);
	GLuint getTextureId(int index);
	GLint getAttributeId(int index);
	GLint getUniformId(int index);
	GLuint getProgramId(int index);
	std::vector<GLuint> getProgramsIds();
	char* getShaderFileName(int index);
	
	glm::mat4 getModelMatrix();
	
	
	////add
	void addVertice(glm::vec4 verticeCoordenates);
	void addVertice(glm::vec3 verticeCoordenates);
	void addNormal(glm::vec3 verticeNormal);
	void addTextureCoordenate(glm::vec2 _textureCoordenates);
	void addElement(GLushort element);
	void addTextureFilesName(const char* fileName);
	
	////setters 
	void setVectorVertices(vector<glm::vec4> _vertices);
	void setVectorNormals(vector<glm::vec3> _normals) ;
	void setVectorTextureCoordenates(vector<glm::vec2>);
	void setVectorTangents(vector<glm::vec3>);
	void setVectorElement(vector<GLushort>);
	
	void setTextureID(int index,GLuint textureID);
	
	void setModelMatrix(glm::mat4 _modelMatrix);

	/*target  (https://www.opengl.org/sdk/docs/man3/xhtml/glBufferData.xml)
                    Specifies the target buffer object.
                    The symbolic constant must be
                    GL_ARRAY_BUFFER,
                    GL_COPY_READ_BUFFER,
                    GL_COPY_WRITE_BUFFER,
                    GL_ELEMENT_ARRAY_BUFFER,
                    GL_PIXEL_PACK_BUFFER,
                    GL_PIXEL_UNPACK_BUFFER,
                    GL_TEXTURE_BUFFER,
                    GL_TRANSFORM_FEEDBACK_BUFFER, or
                    GL_UNIFORM_BUFFER.
                size
                    Specifies the size in bytes of the buffer object's new data store.
                data
                    Specifies a pointer to data that will be copied into the data store for initialization,
                    or NULL if no data is to be copied.
                usage
                    Specifies the expected usage pattern of the data store. The symbolic constant must be
                    GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, 
                    GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, 
                    GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY.
    */
	void storeDataInBuffer(GLuint VAO_ID,GLuint VBO_ID, GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage);
	
	void generateVAOIds(int numberIds);
	void generateVBOIds(int numberIds);
	void generateTextureIds(int numberIds);
	void generateTextureIdUsingSOIL(const char *filename, int force_channels, unsigned int reuse_texture_ID, unsigned int flags);
	void generateNullTextureIds(int numberIds);
	void generateAttributeId(GLuint programID,const char* attributeName);
	void generateUniformId(GLuint programID, const char* uniformName);
	void createProgramId (const char* vertexShaderFileName, const char* fragmentShaderFileName );	
	
	////
	void myReadObj(char* fileName);
	void initGlmModelObject();
	
};


#endif
