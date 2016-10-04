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
	./CarDriving

compile: main.cpp glm_mod.o SOIL.o image_helper.o image_DXT.o stb_image_aug.o
	$(CC) glm_mod.o SOIL.o image_helper.o image_DXT.o stb_image_aug.o  main.cpp  -o CarDriving $(GL_OPTIONS)

SOIL.o: SOIL.c
	$(CC) -c $(GL_OPTIONS) SOIL.c

glm_mod.o: glm_mod.c
	$(CC) -c $(GL_OPTIONS) glm_mod.c

image_helper.o: image_helper.c
	$(CC) -c $(GL_OPTIONS) image_helper.c

image_DXT.o:image_DXT.c
	$(CC) -c $(GL_OPTIONS) image_DXT.c

stb_image_aug.o:stb_image_aug.c
	$(CC) -c $(GL_OPTIONS) stb_image_aug.c

clean:
	 rm -f *.o all