

OBJECTS=main.o ObjParser.o VertexNormal.o Vertex.o Face.o Objet3D.o
LIBS=-lGL -lglut -lGLU
EXEC=TuxTrains
INCLUDES=-I includes/

all:$(EXEC) clean


$(EXEC): main.o ObjParser.o VertexNormal.o Vertex.o Face.o Objet3D.o
	g++ -Wall -o $@ $^ $(LIBS)

main.o: src/main.cpp
	g++ -Wall -c $(INCLUDES) src/main.cpp $(LIBS)

%.o: src/%.cpp
	g++ -Wall -c $(INCLUDES) $^

clean:
	rm *.o;find . -name "*~" | xargs rm

mrproper: clean
	rm -rf $(EXEC)
