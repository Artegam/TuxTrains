#ifndef GL_BOARD_H
#define GL_BOARD_H

#include "Board.h"

//OpenGL libs
#include <GL/glut.h>

namespace glboard {
  class GL_base {
    public:
      virtual void display();
  };

  class GL_Point2D : public board::Point2D {
    public:
      GL_Point2D(board::Point2D pt) {*this = pt;};
      void display();
  };

  class GL_Point3D : public board::Point3D {
    public:
      GL_Point3D(board::Point3D pt) {setCoordinates(pt.getCoordinates());};
      void display();
  };

  class GL_SquareBox : public board::SquareBox {
    public:
      GL_SquareBox(std::map<std::pair<unsigned int, unsigned int>, board::Point3D> data);
      void display();
      void display(GL_Point3D pt);
  };

  class GL_Field : public board::Field {
    public:
      GL_Field(unsigned int width = 1, unsigned int height = 1);
      void display();
  };
}


#endif
