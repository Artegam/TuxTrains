#include "GL_Board.h"

void glboard::GL_Light::init() {
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat mat_shininess[] = { 50.0 };
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel (GL_SMOOTH);

  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}

void glboard::GL_Light::display() {
  glboard::GL_Point3D(*this).display();
  std::vector<double> vec = getCoordinates();
  GLfloat light_position[] = { (GLfloat)vec[0], (GLfloat)vec[1], (GLfloat)vec[2], 0.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}
