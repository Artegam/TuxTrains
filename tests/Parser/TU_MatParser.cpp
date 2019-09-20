
#include "TU_MatParser.h"
#include "MatParser.h"
#include "Material.h"
#include <map>

int TU_MatParser::execute() {

  MatParser p;

  map<string, Material> res = p.readFile("mtl/jaguard.mtl");

  return 0;
}
