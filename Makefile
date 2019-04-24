

SRC=src/
SRC_PARSER=$(SRC)Parser/
SRC_RENDER=$(SRC)Render/

INC=includes/
INC_PARSER=$(INC)Parser/
INC_RENDER=$(INC)Render/

INCLUDES=-I $(INC) -I $(INC_PARSER) -I $(INC_RENDER)

INSTALL_DIR=/usr/bin/

LIBS=-lGL -lglut -lGLU
EXEC=TuxTrains
OPT=-Wall

OBJECTS=main.o ObjParser.o Objet3D.o Face.o Vertex.o VertexNormal.o

all:$(EXEC) clean


$(EXEC): $(OBJECTS)
	g++ $(OPT) $(INCLUDES) -o $@ $^ $(LIBS)

main.o: src/main.cpp
	g++ $(OPT) -c $(INCLUDES) src/main.cpp $(LIBS)

%.o: $(SRC)%.cpp $(SRC_PARSER)%.cpp $(SRC_RENDER)%.cpp
	g++ $(OPT) -c $(INCLUDES) $^

%.o: $(SRC_PARSER)%.cpp
	g++ $(OPT) -c $(INCLUDES) $^

%.o: $(SRC_RENDER)%.cpp
	g++ $(OPT) -c $(INCLUDES) $^

clean:
	rm *.o;find . -name "*~" | xargs rm

mrproper: clean
	rm -rf $(EXEC)

install:
	cp $(EXEC) $(INSTALL_DIR)

uninstall:
	rm $(INSTALL_DIR)$(EXEC)
