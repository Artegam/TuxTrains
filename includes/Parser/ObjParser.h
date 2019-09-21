
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <map>
#include "Objet3D.h"
#include <fstream>
#include <iostream>
#include "Material.h"
#include "Face.h"
#include <regex>

class ObjParser {

  protected:
    map<string, Material> materiaux;
    vector<Objet3D> objets;
    Objet3D * vObj;
    vector<string> fichierRAM;

    int parserFace(smatch m);

  public:

    ObjParser(map<string, Material> mats);

    vector<Objet3D> readFile (const char * filename);
    void parserFichier(void);
    vector<string> getTokens(vector<string>::iterator it);

};
