include $(shell ls config.mak 2>/dev/null)
OS = $(shell uname -s)

# Mac
ifeq ($(OS), Darwin)
	CC = g++
	INCLUDES = -I/opt/local/include
	LIBS = -framework OpenGL -framework GLUT -framework ApplicationServices -lGLEW -lm $(MY_LIBS)
	FLAGS =
endif
# Linux
ifeq ($(OS), Linux)
	CC = g++
	INCLUDES =
	LIBS = -Wall -lm -lGL -lglut -lGLEW -lGLU $(MY_LIBS)
	FLAGS =
endif

GL_OPTIONS = $(LIBS)

run:compile clean
	./MyGame

compile: main.cpp glm_mod.o SOIL.o image_helper.o image_DXT.o stb_image_aug.o Reader.o MyMesh.o Camera.o Car.o MouseEventManager.o Spheres.o KeyBoardEventManager.o Mirror.o Gun.o SkyBox.o Soldier.o  
	$(CC) Reader.o KeyBoardEventManager.o Mirror.o Spheres.o MouseEventManager.o Gun.o SkyBox.o Camera.o MyMesh.o Car.o Soldier.o glm_mod.o SOIL.o image_helper.o image_DXT.o stb_image_aug.o $(GL_OPTIONS) main.cpp  -o MyGame

SOIL.o: external_files/SOIL.c
	$(CC) -c $(GL_OPTIONS) external_files/SOIL.c

glm_mod.o: external_files/glm_mod.c
	$(CC) -c $(GL_OPTIONS) external_files/glm_mod.c

image_helper.o: external_files/image_helper.c
	$(CC) -c $(GL_OPTIONS) external_files/image_helper.c

image_DXT.o:external_files/image_DXT.c
	$(CC) -c $(GL_OPTIONS) external_files/image_DXT.c

stb_image_aug.o:external_files/stb_image_aug.c
	$(CC) -c $(GL_OPTIONS) external_files/stb_image_aug.c
	
Reader.o: Reader.cpp SOIL.o glm_mod.o
	$(CC) -c SOIL.o glm_mod.o $(GL_OPTIONS) Reader.cpp

MyMesh.o: MyMesh.cpp Reader.o
	$(CC) -c $(GL_OPTIONS) MyMesh.cpp 

Camera.o: Camera.cpp MyMesh.o
	$(CC) -c $(GL_OPTIONS) Camera.cpp 

Car.o: Car.cpp MyMesh.o
	$(CC) -c $(GL_OPTIONS) Car.cpp  

MouseEventManager.o: Camera.o MouseEventManager.cpp
	$(CC) -c $(GL_OPTIONS) MouseEventManager.cpp

Spheres.o: MyMesh.o Spheres.cpp
	$(CC) -c $(GL_OPTIONS) Spheres.cpp 

KeyBoardEventManager.o: Car.o Camera.o MouseEventManager.o KeyBoardEventManager.cpp
	$(CC) -c $(GL_OPTIONS) KeyBoardEventManager.cpp

Mirror.o: MyMesh.o Mirror.cpp
	$(CC) -c $(GL_OPTIONS) Mirror.cpp 

Gun.o: MyMesh.o Gun.cpp
	$(CC) -c $(GL_OPTIONS) Gun.cpp 

SkyBox.o: MyMesh.o SkyBox.cpp
	$(CC) -c $(GL_OPTIONS) SkyBox.cpp 
	
House.o: MyMesh.o House.cpp
	$(CC) -c $(GL_OPTIONS) House.cpp
	
Soldier.o: MyMesh.o Soldier.cpp
	$(CC) -c $(GL_OPTIONS) Soldier.cpp  
	
clean:
	 rm -f *.o all 
