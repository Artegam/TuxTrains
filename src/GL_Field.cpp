#include "GL_Board.h"

glboard::GL_Field::GL_Field(unsigned int width, unsigned int height) : board::Field(width, height) {};
void glboard::GL_Field::display () {
 std::map<std::pair<unsigned int, unsigned int>, board::Point3D> pts = points(); 
  for(unsigned int z = 0; z <= height(); z++)
    for(unsigned int x = 0; x <= width(); x++)
      GL_Point3D(pts[{x, z}]).display();
}
