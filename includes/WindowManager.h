#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <vector>
#include <ctime>

#include <GL/glut.h>

#include "Objet3D.h"
#include "Cube.h"

namespace graphicinterface {
  static vector<Objet3D> objets;
  static time_t now;
  static time_t before;
  static bool start;
  static int frame;
 
  class WindowManager {
    public:
      //static void idle(void);
      //void Reshape(int w, int h);
      static void myidle (void) {
        if(graphicinterface::start) {
          graphicinterface::frame = 0;
          time(&graphicinterface::before);
          graphicinterface::start=false;
        }
        time(&graphicinterface::now);

        graphicinterface::frame++;

        if(difftime(graphicinterface::now, graphicinterface::before) >= 1) {
          printf("FPS : %d\n", graphicinterface::frame);
          graphicinterface::start=true;
        }

        glutPostRedisplay();
        glutSwapBuffers();
      }

      static void render(void);
      static void keyboard(unsigned char c, int x, int y);
      static void mouse(int button, int state, int x, int y);

      void initLight(void);
      void init3D(int argc, char** argv, vector<Objet3D> data);
      void load3DFunc();
  };
};
#endif
