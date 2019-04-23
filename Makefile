

OBJECTS=main.o ObjParser.o VertexNormal.o Vertex.o Face.o Objet3D.o
LIBS=-lGL -lglut -lGLU -I boost_1_70_0
EXEC=essai3D

all:$(EXEC) clean


$(EXEC): main.o ObjParser.o VertexNormal.o Vertex.o Face.o Objet3D.o
	g++ -Wall -o $@ $^ $(LIBS)

main.o: main.cpp
	g++ -Wall -c main.cpp $(LIBS)

%.o: %.cpp
	g++ -Wall -c $^

clean:
	rm *.o

mrproper: clean
	rm -rf $(EXEC)
