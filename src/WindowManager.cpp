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

void graphicinterface::WindowManager::init3D(int argc, char** argv, vector<Objet3D> data) {
  graphicinterface::objets.insert(graphicinterface::objets.begin(), data.begin(), data.end());
  // Pour un écran Widescreen ratio d'aspect = 16:9
  //[ASC] penser a une struct ?
  long width = 800;
  long height = 450;
  glutInit(&argc, argv); // https://www.opengl.org/resources/libraries/glut/spec3/node10.html
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

  glutInitWindowPosition(100, 100);
  glutInitWindowSize(width, height);
  glutCreateWindow(argv[1]);

  //Initialisation des matrices
  initLight();

  //Initialisation des objets (chargement dans la carte graphique pour le rendu
  for(vector<Objet3D>::iterator it = graphicinterface::objets.begin(); it != graphicinterface::objets.end(); it++)
    it->init();
  graphicinterface::start = true;
}

void graphicinterface::WindowManager::Reshape(int w, int h) {
  long width = 800;
  long height = 450;
  float zNear = 0.1;
  float zFar = 50.0;
  float zoomFactor = 1.0;

  glViewport(0, 0, (GLint)w, (GLint)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective (50.0*zoomFactor, (float)width/(float)height, zNear, zFar);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  moveCamera();
}

void graphicinterface::WindowManager::moveCamera () {
  vector<double> vecPos = cameraPos.getCoordinates();
  vector<double> vecTarget = cameraTarget.getCoordinates();
  vector<double> vecUp = cameraUpVector.getCoordinates();
  gluLookAt(vecPos[0], vecPos[1], vecPos[2], vecTarget[0], vecTarget[1], vecTarget[2], vecUp[0], vecUp[1], vecUp[2]);
}

void graphicinterface::WindowManager::drawview3D () {
  //[ASC] drawing...
  glRotatef(graphicinterface::angle, 0.0, 1.0, 0.0);

/*
  for(vector<Objet3D>::iterator it = graphicinterface::objets.begin(); it != graphicinterface::objets.end(); it++)
    it->dessiner();
*/
/*
  Case c;
  Objet3D o = c.toObjet3D();
  o.setNom((char*)string("terrain").c_str());
  o.init();
  o.dessiner();
*/
/*
  glboard::GL_SquareBox cell;
  cell.display();
*/
  glboard::GL_Field field(10, 10);
  field.display();
}

void graphicinterface::WindowManager::print (const char * txt) {
  for (unsigned int i = 0; i < strlen(txt); i++)
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, txt[i]); // Affiche chaque caractère de la chaîne
}

void graphicinterface::WindowManager::drawview2D () {
  long height = 450;
  //[ASC] 2D drawing...
  unsigned int x, y;
  x = 10;
  y = height-15;
  glRasterPos2f(x, y);

  //glLoadIdentity();
  char txt[20];
  sprintf(txt, "FPS : %d", graphicinterface::fps);
  graphicinterface::WindowManager::print(txt);

  y = height-(15*2);
  glRasterPos2f(x, y);
  sprintf(txt, "angle : %f", graphicinterface::angle);
  graphicinterface::WindowManager::print(txt);
}

void graphicinterface::WindowManager::render(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glProjBegin();
  drawview3D();

  //[ASC] 2D view configuration
  glOrthoBegin();
  drawview2D();
  glOrthoEnd();
  glutSwapBuffers();
}

void graphicinterface::WindowManager::keyboard(unsigned char c, int x, int y) {
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
