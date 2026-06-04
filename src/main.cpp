#include <iostream>
#include <vector>

#include "ObjParser.h"
#include "Objet3D.h"
#include "WindowManager.h"


using namespace std;

//Ligne de commande de compilation
//g++ monPremierEssai.cpp -lGL -lglut -o monPremierEssai

int main(int argc, char** argv) {
  ObjParser * parser = new ObjParser();

  std::vector<string> obj_files;
  obj_files.push_back("obj/jaguard.obj");
  //obj_files.push_back("obj/maison.obj");
  //obj_files.push_back("rail.obj");
  //obj_files.push_back("The_rocket_locomotive_1800_pour_integration.obj");

  for(std::vector<string>::iterator files = obj_files.begin(); files!=obj_files.end(); files++) {
    printf("Lecture du fichier... \t %s\n", (*files).c_str());
    graphicinterface::objets = parser->readFile((*files).c_str());
  }

  parser->~ObjParser();
  graphicinterface::WindowManager w;
  w.init3D(argc, argv);

  w.load3DFunc();
  glutMainLoop(); //[ASC] est-ce le chargement de la fonction ??
}
