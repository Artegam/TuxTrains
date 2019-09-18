#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <regex>

#include "Material.h"
#include "Objet3D.h"

using namespace std;

class Loader {

  protected:
    map<string, Material> listeMateriaux;
    vector<Objet3D> objets;

    vector<string> getFilenamesFromDir(const char* directory);

  public:
    Loader(vector<string> listeObj, vector<string> listeMtl);
    Loader(const char* cheminObj, const char* cheminMtl, bool recursif);
    vector<Objet3D> getObjets();

};
