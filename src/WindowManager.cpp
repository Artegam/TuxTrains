#include "WindowManager.h"

void graphicinterface::WindowManager::initLight(void) {
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat mat_shininess[] = { 50.0 };
  GLfloat light_position[] = { 4.0, 4.0, 4.0, 0.0 };
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel (GL_SMOOTH);

  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}

void graphicinterface::WindowManager::init3D(int argc, char** argv) {
  // Pour un écran Widescreen ratio d'aspect = 16:9
  //[ASC] penser a une struct ?
  long width = 800;
  long height = 450;
  float zNear = 0.1;
  float zFar = 50.0;
  float zoomFactor = 1.0;

  glutInit(&argc, argv); // https://www.opengl.org/resources/libraries/glut/spec3/node10.html
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

  glutInitWindowPosition(100, 100);
  glutInitWindowSize(width, height);
  glutCreateWindow(argv[1]);

  //Initialisation des matrices
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective (50.0*zoomFactor, (float)width/(float)height, zNear, zFar);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glMatrixMode(GL_TEXTURE);
  glLoadIdentity();

  glMatrixMode(GL_MODELVIEW);

  initLight();
  gluLookAt(0.0, 6.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  //Initialisation des objets (chargement dans la carte graphique pour le rendu
  for(vector<Objet3D>::iterator it = graphicinterface::objets.begin(); it != graphicinterface::objets.end(); it++)
    it->init();
  graphicinterface::start = true;
}

/*
void graphicinterface::WindowManager::Reshape(int w, int h) {
  glViewport( 0, 0, (GLint)w, (GLint)h );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glFrustum( -1.0, 1.0, -1.0, 1.0, 1.5, 100.0);
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
}
*/

void graphicinterface::WindowManager::render(void) {
  int angle = -1;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glRotatef(angle, 0.0, 1.0, 0.0);

  Cube c;
  c.init();
  c.display();
  //[ASC] ici il y a un soucis avec dessiner les objets - pas encore trouvé d'ou vebait l'erreur....
  for(vector<Objet3D>::iterator it = graphicinterface::objets.begin(); it != graphicinterface::objets.end(); it++)
    it->dessiner();

  glutSwapBuffers();
  glFlush();
}

void graphicinterface::WindowManager::keyboard(unsigned char c, int x, int y){
  // ASCH - 29/09/2014 - La touche 27 est la touche echap
  if (c == 27) exit(0);
}

void graphicinterface::WindowManager::mouse(int button, int state, int x, int y){
  if(button == GLUT_RIGHT_BUTTON) exit(0);
}

void graphicinterface::WindowManager::load3DFunc() {
  glutDisplayFunc(render);
  glutIdleFunc(graphicinterface::WindowManager::myidle);
  //glutReshapeFunc(Reshape);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
}
