
#include "MatParser.h"
#include "Material.h"
#include <map>

int main(int argc, char** argv) {

  MatParser p;

  map<string, Material> res = p.readFile("mtl/jaguard.mtl");

  return 0;
}
