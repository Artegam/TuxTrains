

OBJECTS=main.o VertexNormal.o Vertex.o Face.o Objet3D.o
PARSER=src/Parser/ObjParser.o
LIBS=-lGL -lglut -lGLU
EXEC=TuxTrains
INCLUDES=-I includes/
OPT=-Wall

all:$(EXEC) clean


$(EXEC): $(OBJECTS) $(PARSER)
	g++ $(OPT) -o $@ $^ $(LIBS)

main.o: src/main.cpp
	g++ $(OPT) -c $(INCLUDES) src/main.cpp $(LIBS)

src/Parser/%.o: src/Parser/%.cpp
	g++ $(OPT) -c $(INCLUDES) $(INCLUDES)Parser/ $^ -o $@

%.o: src/%.cpp
	g++ $(OPT) -c $(INCLUDES) $^

clean:
	rm *.o;find . -name "*~" | xargs rm

mrproper: clean
	rm -rf $(EXEC)
