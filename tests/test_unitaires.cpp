
#include "TU_Loader.h"
#include "TU_MatParser.h"
#include "TU_Moteur.h"

int main(int argc, char** argv) {

  TU_Loader t_load;
  t_load.execute();

  TU_MatParser t_matparser;
  t_matparser.execute();

  TU_Moteur t_moteur;
  t_moteur.execute();

  return 0;
}
