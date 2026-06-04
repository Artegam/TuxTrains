#ifndef CUBE_H
#define CUBE_H


#include <GL/glut.h>

class Cube {
  private:
    GLfloat light_diffuse[4] = {1.0, 0.0, 0.0, 1.0};  /* Red diffuse light. */
    GLfloat light_position[4] = {1.0, 1.0, 1.0, 0.0};  /* Infinite light location. */
    GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
      {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
      {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
    GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
      {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
      {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
    GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */

  public:
    void drawBox (void);
    void display (void);
    void init (void);

};

#endif
