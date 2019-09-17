#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

#include "Material.h"

using namespace std;

class Loader {

  protected:
    map<string, Material> listeMateriaux;

  public:
    Loader(vector<string> listeObj, vector<string> listeMtl);
    Loader(const char* cheminObj, const char* cheminMtl, bool recursif);

    vector<string> getFilenamesFromDir(const char* directory);
};
