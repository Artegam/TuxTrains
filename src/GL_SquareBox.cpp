#include "GL_Board.h"
#include <stdio.h>

glboard::GL_SquareBox::GL_SquareBox(std::map<std::pair<unsigned int, unsigned int>, board::Point3D> data) : board::SquareBox(data) {};
void glboard::GL_SquareBox::display () {
  std::map<std::pair<unsigned int, unsigned int>, board::Point3D> points = getPoints();

  glBegin(GL_TRIANGLES);

  //Soit 4 points ABCD
  //Dessiner ABC
  //calculer le vecteur normal
  board::Point3D normal1 = computeNormal ({points[{1, 1}], points[{0, 0}], points[{0, 1}]});
  displayNormal(normal1);
  displayVertex(GL_Point3D(points[{0, 0}]));
  displayVertex(GL_Point3D(points[{0, 1}]));
  displayVertex(GL_Point3D(points[{1, 1}]));

  //Dessiner ACD
  //[ASC] ordre pour la normale changee because racine carree negative donne la valeur nan
  board::Point3D normal2 = computeNormal ({points[{1, 1}], points[{1, 0}], points[{0, 0}]});
  displayNormal(normal2);
  displayVertex(GL_Point3D(points[{0, 0}]));
  displayVertex(GL_Point3D(points[{1, 1}]));
  displayVertex(GL_Point3D(points[{1, 0}]));

  glEnd();

  DrawNormals(GL_Point3D(points[{0, 0}]), normal1);
  DrawNormals(GL_Point3D(points[{0, 1}]), {0.0, 1.0, 0.0});
  DrawNormals(GL_Point3D(points[{1, 1}]), {0.0, 1.0, 0.0});

  DrawNormals(GL_Point3D(points[{0, 0}]), {0.0, 1.0, 0.0});
  DrawNormals(GL_Point3D(points[{1, 1}]), {0.0, 1.0, 0.0});
  DrawNormals(GL_Point3D(points[{1, 0}]), {0.0, 1.0, 0.0});
}

void glboard::GL_SquareBox::displayNormal(GL_Point3D pt) {
  std::vector<double> vec = pt.getCoordinates();
  glNormal3f(vec[0], vec[1], vec[2]); //[ASC] les normales pour la lumière
}

void glboard::GL_SquareBox::displayVertex(GL_Point3D pt) {
  std::vector<double> vec = pt.getCoordinates();
  glVertex3f(vec[0], vec[1], vec[2]);
}

board::Point3D glboard::GL_SquareBox::computeNormal (std::vector<board::Point3D> triangle) {
  board::Point3D A = triangle[0];
  board::Point3D B = triangle[1];
  board::Point3D C = triangle[2];

  std::vector<double> vecA = A.getCoordinates();
  std::vector<double> vecB = B.getCoordinates();
  std::vector<double> vecC = C.getCoordinates();

  //[ASC] compute u et v
  board::Point3D U(vecB[0]-vecA[0], vecB[1]-vecA[1], vecB[2]-vecA[2]);
  board::Point3D V(vecC[0]-vecA[0], vecC[1]-vecA[1], vecC[2]-vecA[2]);
  std::vector<double> vecU = U.getCoordinates();
  std::vector<double> vecV = V.getCoordinates();

  //[ASC] cross product
  double x = vecU[1]*vecV[2]-vecU[2]*vecV[1];
  double y = vecU[2]*vecV[0]-vecU[0]*vecV[2];
  double z = vecU[0]*vecV[1]-vecU[1]*vecV[0];

  if(x<0) x=-x;
  if(y<0) y=-y;
  if(z<0) z=-z;

  board::Point3D N(x, y, z);

  //[ASC] normalize
  std::vector<double> vecN = N.getCoordinates();
  double length = std::sqrt(vecN[0]*vecN[0]+vecN[1]*vecN[1]+vecN[2]*vecN[2]);
  if(length == 0) length = 1.0; //[ASC] sqrt returns sometimes 0 instead of 1
  board::Point3D Nnorm(vecN[0]/length, vecN[1]/length, vecN[2]/length);

  return Nnorm;
}

void glboard::GL_SquareBox::DrawNormals(glboard::GL_Point3D pt, board::Point3D norm) {
  std::vector<double> vec = pt.getCoordinates();
  std::vector<double> vecN = norm.getCoordinates();
  glDisable(GL_LIGHTING);
  glColor3f(0.17f, 1.0f, 1.0f); // cyan
  const float scale = 0.2f;
  glBegin(GL_LINES);
  // Start of line
  glVertex3f(vec[0], vec[1], vec[2]);

  // End of line
  glVertex3f(
      vec[0] + vecN[0] * scale,
      vec[1] + vecN[1] * scale,
      vec[2] + vecN[2] * scale
  );
  glEnd();
  glColor3f(1.0f, 1.0f, 1.0f); // white
  glEnable(GL_LIGHTING);
}
