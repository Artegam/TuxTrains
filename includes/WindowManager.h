#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <vector>
#include <ctime>
#include <cstring>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Objet3D.h"
#include "GL_Board.h"

namespace graphicinterface {
  static vector<Objet3D> objets;
  static time_t now;
  static time_t before;
  static bool start;
  static int frame;
  static int fps;
  static int angle;
  static board::Point3D cameraPos((std::vector<double>){0.0, 6.0, 6.0});
  static board::Point3D cameraTarget((std::vector<double>){0.0, 0.0, 0.0});
  static board::Point3D cameraUpVector((std::vector<double>){0.0, 1.0, 0.0});
 
  class WindowManager {
    public:
      static void glOrthoBegin() {
        long width = 800;
        long height = 450;
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0.0, width, 0.0, height, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
      };
      static void glOrthoEnd() {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
      };
      static void glProjBegin() {
        long width = 800;
        long height = 450;
        float zNear = 0.1;
        float zFar = 100.0;
        float zoomFactor = 1.0;

        //[ASC] 3D view configuration
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective (45.0*zoomFactor, (float)width/(float)height, zNear, zFar);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0.0, 6.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
      };
      static void glProjEnd() {
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
      };
      static void drawview3D ();
      static void drawview2D ();
      static void Reshape(int w, int h);
      static void moveCamera();
      static void myidle (void) {
        if(graphicinterface::start) {
          graphicinterface::frame = 0;
          time(&graphicinterface::before);
          graphicinterface::start=false;
        }
        time(&graphicinterface::now);

        graphicinterface::frame++;

        if(difftime(graphicinterface::now, graphicinterface::before) >= 1) {
          char txt[20];
          sprintf(txt, "FPS : %d\n", graphicinterface::frame);
          unsigned int x, y, z;
          x = 50;
          y = 50;
          z = 0;
          glRasterPos3f(x, y, z);
          graphicinterface::start=true;
          graphicinterface::fps=graphicinterface::frame;
        }

        graphicinterface::angle++;
        glutPostRedisplay();
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
