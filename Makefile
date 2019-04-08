

OBJECTS=main.o ObjParser.o VertexNormal.o Vertex.o Face.o Objet3D.o
LIBS=-lGL -lglut -lGLU
EXEC=essai3D

all:$(EXEC) clean


$(EXEC): main.o ObjParser.o VertexNormal.o Vertex.o Face.o Objet3D.o
	g++ -o $@ $^ $(LIBS)

main.o: main.cpp
	g++ -c main.cpp $(LIBS)

%.o: %.cpp
	g++ -c $^

clean:
	rm *.o

mrproper: clean
	rm -rf $(EXEC)
