#include "TU_Moteur.h"
#include "Moteur.h"

int TU_Moteur::execute() {

  Moteur *m = new Moteur("obj/");
  m->tic();

  return 0;
}
