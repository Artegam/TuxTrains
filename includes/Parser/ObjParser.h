#ifndef OBJPARSER_H
#define OBJPARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <map>
#include "Objet3D.h"
#include <fstream>
#include <iostream>
#include "Material.h"
#include "MatParser.h"
#include "Face.h"
#include <regex>

class ObjParser {

  protected:
    map<string, Material> materiaux;
    Objet3D * vObj;
    vector<string> fichierRAM;

    Face parserFace(string m);
    string cheminFichiersObj;
    MatParser matParser;
    Material mat_courant;

  public:

    ObjParser();

    vector<Objet3D> readFile (const char * filename, const char * chemin);
    vector<Objet3D> parserFichier(void);
    vector<string> getTokens(vector<string>::iterator it);
    vector<string> split (string s, string delimiter);

};

#endif

