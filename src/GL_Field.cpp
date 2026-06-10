#include "GL_Board.h"

glboard::GL_Field::GL_Field(unsigned int width, unsigned int height) : board::Field(width, height) {};
void glboard::GL_Field::display () {
  board::Point3D center = getCenter();
  std::vector<double> data = center.getCoordinates();
  glTranslatef(-data[0], -data[1], -data[2]);
  std::map<std::pair<unsigned int, unsigned int>, board::Point3D> pts = points();
  for(unsigned int z = 0; z <= height(); z++)
    for(unsigned int x = 0; x <= width(); x++) {
      //Afficher les points
      //GL_Point3D(pts[{x, z}].display();
      //Afficher les surfaces
      std::map<std::pair<unsigned int, unsigned int>, board::Point3D> points;
      points.insert(std::make_pair(std::make_pair(0, 0), pts[{x, z}]));
      points.insert(std::make_pair(std::make_pair(0, 1), pts[{x, z+1}]));
      points.insert(std::make_pair(std::make_pair(1, 0), pts[{x+1, z}]));
      points.insert(std::make_pair(std::make_pair(1, 1), pts[{x+1, z+1}]));
      GL_SquareBox box(points);
      box.display();
    }
  glTranslatef(data[0], data[1], data[2]);
}
