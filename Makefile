

VPATH = src:src/Parser:src/Render

SRC_TU = tests/
SRC_TU_PARSER = $(SRC_TU)Parser/
SRC_TU_RENDER = $(SRC_TU)Render/

INC = includes/
INC_PARSER = $(INC)Parser/
INC_RENDER = $(INC)Render/

INC_TU = $(SRC_TU)$(INC)

OUT = o/
BIN = bin/

INCLUDES = -g -I $(INC) -I $(INC_PARSER) -I $(INC_RENDER) -I $(INC_TU)

INSTALL_DIR = /usr/bin/

LIBS =-lGL -lglut -lGLU
EXEC = TuxTrains
OPT = -Wall

O_PARSER = ObjParser.o MatParser.o Loader.o
OBJECTS = $(O_PARSER) Objet3D.o Face.o Vertex.o VertexNormal.o Material.o Moteur.o

TESTS_U = test_unitaires
O_TESTS_U = $(OBJECTS) test_unitaires.o TU_Loader.o TU_Moteur.o TU_MatParser.o

#all:$(EXEC) $(TESTS_U)
all:$(EXEC)


$(EXEC): main.o $(OBJECTS)
	g++ $(OPT) $(INCLUDES) o/*.o $(LIBS) -o $(BIN)$@
	rm o/main.o

$(TESTS_U): $(O_TESTS_U)
	g++ $(OPT) $(INCLUDES) -o $(BIN)$@ o/*.o $(LIBS)

main.o: main.cpp
	g++ $(OPT) -c $(INCLUDES) $^ $(LIBS) -o o/$@

%.o: %.cpp
	g++ $(OPT) -c $(INCLUDES) $^ -o o/$@

%.o: $(SRC_TU)%.cpp
	g++ $(OPT) -c $(INCLUDES) $^ -o o/$@

%.o: $(SRC_TU_PARSER)%.cpp
	g++ $(OPT) -c $(INCLUDES) $^ -o o/$@

%.o: $(SRC_TU_RENDER)%.cpp
	g++ $(OPT) -c $(INCLUDES) $^ -o o/$@

clean:
	rm o/*.o;find . -name "*~" | xargs rm -f

mrproper: clean
	rm -rf $(EXEC)

install:
	cp $(EXEC) $(INSTALL_DIR)

uninstall:
	rm $(INSTALL_DIR)$(EXEC)
