

SRC=src/
SRC_PARSER=$(SRC)Parser/
SRC_RENDER=$(SRC)Render/

SRC_TU=tests/
SRC_TU_PARSER=$(SRC_TU)Parser/

INC=includes/
INC_PARSER=$(INC)Parser/
INC_RENDER=$(INC)Render/

INCLUDES=-I $(INC) -I $(INC_PARSER) -I $(INC_RENDER)

INSTALL_DIR=/usr/bin/

LIBS=-lGL -lglut -lGLU
EXEC=TuxTrains
OPT=-Wall

O_PARSER=ObjParser.o MatParser.o
OBJECTS=$(O_PARSER) Objet3D.o Face.o Vertex.o VertexNormal.o Material.o

TESTS_U=TU_MatParser
O_TESTS_U=TU_MatParser.o $(OBJECTS)

all:$(EXEC) $(TESTS_U)


$(EXEC): main.o $(OBJECTS)
	g++ $(OPT) $(INCLUDES) -o $@ $^ $(LIBS)

$(TESTS_U): $(O_TESTS_U)
	g++ $(OPT) $(INCLUDES) -o $@ $^ $(LIBS)

main.o: src/main.cpp
	g++ $(OPT) -c $(INCLUDES) src/main.cpp $(LIBS)

%.o: $(SRC)%.cpp
	g++ $(OPT) -c $(INCLUDES) $^

%.o: $(SRC_PARSER)%.cpp
	g++ $(OPT) -c $(INCLUDES) $^

%.o: $(SRC_RENDER)%.cpp
	g++ $(OPT) -c $(INCLUDES) $^

%.o: $(SRC_TU)%.cpp
	g++ $(OPT) -c $(INCLUDES) $^

%.o: $(SRC_TU_PARSER)%.cpp
	g++ $(OPT) -c $(INCLUDES) $^

clean:
	rm *.o;find . -name "*~" | xargs rm -f

mrproper: clean
	rm -rf $(EXEC)

install:
	cp $(EXEC) $(INSTALL_DIR)

uninstall:
	rm $(INSTALL_DIR)$(EXEC)
