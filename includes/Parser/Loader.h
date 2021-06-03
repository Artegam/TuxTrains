#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <regex>
#include <list>

#include "Material.h"
#include "Objet3D.h"

using namespace std;

class Loader {

  protected:
    map<string, Material> listeMateriaux;
    map<string, Objet3D> objets;

    vector<string> getFilenamesFromDir(const char* directory);

  public:
    Loader(const char* cheminObj, bool recursif);
    map<string, Objet3D> getObjets();

};
