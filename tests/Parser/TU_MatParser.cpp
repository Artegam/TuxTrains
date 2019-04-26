
#include "MatParser.h"
#include "Material.h"
#include <vector>

int main(int argc, char** argv) {

  MatParser p;

  vector<Material> res = p.readFile("mtl/jaguard.mtl");

  return 0;
}
