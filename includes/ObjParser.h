
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include "Objet3D.h"
#include <fstream>
#include <iostream>
#include "Board.h"

class ObjParser {

  protected:
    vector<Objet3D> objets;
    Objet3D * vObj;

  public:

    //ObjParser();
    //~ObjParser();
    vector<board::SquareBox> readFile (const char * filename);
    vector<std::string> split(std::string str, std::string delimiter);

};
