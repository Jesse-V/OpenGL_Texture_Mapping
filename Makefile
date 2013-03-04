CC=g++
CPPFLAGS=--std=c++0x -g3
LDLIBS=-lglut -lGLEW -lGLEW -lGL
all: Main; ./Main; make clean
Main: World.o Mandelbrot/MandelModel.o Model.o ShaderLoader.o
clean:
	rm -f *.o Main
.PHONY: all clean