#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>

#include "Parser/ObjParser.h"
#include "Parser/MatParser.h"
#include "Parser/Loader.h"
#include "Objet3D.h"
#include "Render/Moteur.h"

using namespace std;

	vector<Objet3D> objets;
	vector<Objet3D>::iterator it;
  map<string, Material> materials;
	// Pour un écran Widescreen ratio d'aspect = 16:9
	long width = 800;
	long height = 450;
  int mouseX = 0;
  int mouseY = 0;
  float rx = 0.0;
  float ry = 0.0;
  float zoomFactor = 1.;
	float zNear = 0.1;
	float zFar = 50.0;

  // Les constantes
  const float MAX_ZOOM = 5.0;

  float camera_pos[3] = {0.0f, 6.0f, 6.0f};
  float camera_cible[3] = {0.0f, 0.0f, 0.0f};

  GLfloat cs[3] = {0.0f, 15.0f, 0.0f}; // Position de LIGHT1
  GLfloat cs2[3] = {0.0f, 0.0f, 15.0f}; // Position de LIGHT1
  bool click = false;
  int mbutton = 0;
  float varLight1 = 0.0;
  float varLight2 = 0.0;
	int angle;
  GLfloat anim =0;
  GLfloat a_step = 0.5;
  static int frame = 0;
  static int current_time = 0;
  static int last_time = 0;
  static double fps = 0.0;     //Le nb de fps
  static bool loumiere = true; //par dÃ©faut allumÃ©  eouteind
  Moteur moteur("./obj"); //Le moteur qui gere le chargement et l'animation des objets en 3D


  char str[150] = "";
  char sMouse[150] = "";

// Prototypes
void initLight(void);
void idle(void);
void Reshape(int w, int h);
void render(void);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void mouseMove(int x, int y);
void vBitmapOutput(int x, int y, char *string, void *font);
void vStrokeOutput(GLfloat x, GLfloat y, char *string, void *font);
void createLight(int light, GLfloat lightpos[], GLfloat lightdiffuse[], GLfloat lightspecular[]);

int main(int argc, char** argv) {

  printf("******************************************************** \n");
  printf("*************  Demarrage de tuxtrain     *************** \n");
  printf("******************************************************** \n");
  MatParser matParser;

	angle = -1.0;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

  glutInitWindowPosition(100, 100);
  glutInitWindowSize(width, height);
  glutCreateWindow(argv[1]);

	//Initialisation des matrices
  glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
  //glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	gluPerspective (50.0*zoomFactor, (float)width/(float)height, zNear, zFar);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);

  initLight();
	gluLookAt(0.0, 6.0, 6.0, 0.0, 0.0, 0.0, 0.0 , 1.0, 0.0);

  moteur.init();
/*
  //Initialisation des objets (chargement dans la carte graphique pour le rendu
	for(it = objets.begin(); it != objets.end(); it++) {
		it->init();
	}
*/
  glutDisplayFunc(render);
  glutIdleFunc(idle);
	//glutReshapeFunc(Reshape);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMove);

  glutMainLoop();
}


void initLight(void)
{

  //LIGHT0
   GLfloat pos[] = {2.0, 2.0, 2.0, 0.0};  //Position de la source lumineuse
   GLfloat diff[] = {0.3, 0.3, 0.5, 0.0}; // QuantitÃ© de couleur reflechie par les objets
   GLfloat spec[] = {0.3, 0.3, 0.5, 0.0}; // Aspect blanc reflete

   createLight(GL_LIGHT0, pos, diff, spec);

   //LIGHT1
   pos[0] = cs[0];pos[1] = cs[1]; pos[2] = cs[2]; pos[3] =  0.0;
   diff[0] = varLight1; diff[1] = varLight1; diff[2] = varLight1; diff[3] = 0.0;
   spec[0] = varLight1; spec[1] = varLight1; spec[2] = varLight1; spec[3] = 0.0;

   createLight(GL_LIGHT1, pos, diff, spec);

   //LIGHT2 (opposee a LIGHT1)
   pos[0] = cs2[0];pos[1] = cs2[1]; pos[2] = cs2[2]; pos[3] =  0.0;
   diff[0] = varLight2; diff[1] = varLight2; diff[2] = varLight2 * 0.4; diff[3] = 0.0;
   spec[0] = varLight2; spec[1] = varLight2; spec[2] = varLight2 * 0.4; spec[3] = 0.0;

   createLight(GL_LIGHT2, pos, diff, spec);

   //exponent propertie defines the concentration of the light
   glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 15.0f);

   //light attenuation (default values used here : no attenuation with the distance)
   glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0f);
   glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0f);
   glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0f);

   glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);
   glEnable(GL_LIGHT2);

}

void createLight(int light, GLfloat lightpos[], GLfloat lightdiffuse[], GLfloat lightspecular[]) {

   glLightfv(light, GL_POSITION, lightpos);
   glLightfv(light, GL_DIFFUSE, lightdiffuse);
   glLightfv(light, GL_SPECULAR, lightspecular);

}

void idle(void) {

  frame++;
  current_time = glutGet(GLUT_ELAPSED_TIME);

  if(current_time - last_time > 1000) {
    fps = frame * 1000.0 / (current_time - last_time);

    sprintf(str, "FPS : %f", fps);
    //vBitmapOutput(10, 10, str, GLUT_BITMAP_8_BY_13);
    last_time = current_time;
    frame = 0;
  }

	glutPostRedisplay();
	glutSwapBuffers();
}

void render(void) {


  // Regler la camera et la profondeur de champs
  GLint w = glutGet(GLUT_WINDOW_WIDTH);
  GLint h = glutGet(GLUT_WINDOW_HEIGHT) ;
  glViewport( 0, 0, w, h);

      glLoadIdentity();
gluLookAt(camera_pos[0]*zoomFactor, camera_pos[1]*zoomFactor, camera_pos[2]*zoomFactor,    /* oeil */
          camera_cible[0], camera_cible[1], camera_cible[2],    /* point observe */
          0.0, 1.0, 0.0);   /* oÃ¹ est le ciel  */
      glutPostRedisplay();

  // Creation de la scene
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  initLight();

  //AZZIZ LOUMIERE !!!
  if(loumiere) {
    glEnable(GL_LIGHT1);
  }else{
    glDisable(GL_LIGHT1);
  }

  glColor3d(1,1,1); // Texte en blanc
  vBitmapOutput(-1,3,str,GLUT_BITMAP_HELVETICA_18);

  glColor3d(1,0,0); // Texte en rouge
  vBitmapOutput(-2,3,sMouse,GLUT_BITMAP_HELVETICA_18);


  //Pour symbolyser la lumiÃ¨re du soleil
  GLfloat es[4] = {0.8f, 0.8f, 0.8f, 1.0f};
  glMaterialfv(GL_FRONT, GL_EMISSION, es);

  glTranslatef(cs[0], cs[1], cs[2]);
  glutSolidSphere(0.25, 6, 6);
  glTranslatef(0-cs[0], 0-cs[1], 0-cs[2]);


  glTranslatef(cs2[0], cs2[1], cs2[2]);
  glutSolidSphere(0.25, 6, 6);
  glTranslatef(0-cs2[0], 0-cs2[1], 0-cs2[2]);


  glPushMatrix();
  //rotation de la scene
  glRotatef(rx, 1., 0., 0.);
  glRotatef(ry, 0., 1., 0.);

  moteur.tic();

  glPopMatrix();

  //Pour symboliser la lumiÃ¨re bleue qui se dÃ©place
  GLfloat e[4] = {0.0f, 0.0f, 0.8f, 1.0f};
  glMaterialfv(GL_FRONT, GL_EMISSION, e);

  //Pour effacer l'objet chargÃ©
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  anim += a_step;
  if (anim == 95.0 || anim == 0.0) a_step = -a_step;


//Pour sauvegarder/restaurer la scene
glPushMatrix();
  GLfloat c[3] = {2.0f, 0.0f, 2.0f};
  GLfloat lightpos[] = {0.0, 0.0, 0.0, 1.0};

  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
  glTranslatef(c[0], c[1], c[2]); //Pose la position
  //glutSolidCube(0.5);
  //glRotatef(anim, 1.0, 0.0, 0.0);

glPopMatrix();


  glutSwapBuffers();
	glFlush();
}

void Reshape(int w, int h)
{
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glFrustum( -1.0, 1.0, -1.0, 1.0, 1.5, 100.0);
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y){
  // ASCH - 29/09/2014 - La touche 27 est la touche echap

  switch (key) {
    case 27: // Escape
      exit(0);
      break;

    case 'l': //l
    //inverser le bit de la lumiere
    loumiere = !loumiere;
    break;

    case 'z': // vers l'avant
    camera_pos[2] -= 2.0;
    camera_cible[2] -=2.0;
    break;

    case 's': //vers l'arriere
    camera_pos[2] += 2.0;
    camera_cible[2] += 2.0;
    break;

    case 'q': //vers la gauche
    camera_pos[0] -= 2.0;
    camera_cible[0] -= 2.0;
    break;

    case 'd': //vers la droite
    camera_pos[0] += 2.0;
    camera_cible[0] += 2.0;
    break;

    case 'a': // rotation gauche
    ry -= fmod(90. * 5.0 / height, 360.);
    break;

    case 'e': // rotation droite
    ry += fmod(90. * 5.0 / height, 360.);
    break;

    case 'I':
    camera_pos[0] = 0.0; camera_pos[1] = 0.0; camera_pos[2] = 6.0;
    camera_cible[0] = 0.0; camera_cible[1] = 0.0; camera_cible[2] = 0.0;
    break;

   // Axes de rotations
   case 'x':
   case 'X':
      glRotatef(30.,1.0,0.0,0.0);
      glutPostRedisplay();
      break;
   case 'y':
   case 'Y':
      glRotatef(30.,0.0,1.0,0.0);
      glutPostRedisplay();
      break;

  case 'c':
  if(varLight1 < 1.0) {varLight1 += 0.1;}
  break;
  case 'v':
  if(varLight1 > 0.0) {varLight1 -= 0.1;}
  break;
  case 'b':
  if(varLight2 < 1.0) {varLight2 += 0.1;}
  break;
  case 'n':
  if(varLight2 > 0.0) {varLight2 -= 0.1;}
  break;

  }
}

void mouse(int button, int state, int x, int y){

  switch (button) {
    case GLUT_RIGHT_BUTTON: //rotations
      click = !click;
      mbutton = GLUT_RIGHT_BUTTON;
      mouseX = x;
      mouseY = y;
      break;

    case GLUT_LEFT_BUTTON: // Deplacements
      // Par exemple ici ajouter un rail
      click = !click;
      mbutton = GLUT_LEFT_BUTTON;
      mouseX = x;
      mouseY = y;
      break;

    case GLUT_MIDDLE_BUTTON: // Zoom
      click = !click;
      mbutton = GLUT_MIDDLE_BUTTON;
      break;
  }
}

void mouseMove(int x, int y) {
  //TODO: mettre juste la molette au lieu du click du bouton du milieu
  if(click && mbutton == GLUT_MIDDLE_BUTTON) {
    // Zoom
    zoomFactor += 0.05 * (mouseY - y);
    if(zoomFactor < 0.1){
      zoomFactor = 0.1;
    }else if (zoomFactor > MAX_ZOOM) {
      zoomFactor = MAX_ZOOM;
    }
  } else if (click && mbutton == GLUT_RIGHT_BUTTON) {
    rx += fmod(90. * (mouseY - y) / height, 360.);
    ry += fmod(90. * (mouseX - x) / width, 360.);
  } else if (click && mbutton == GLUT_LEFT_BUTTON) {
    //vers l'avant / arriere
    camera_pos[2] += 10. * (mouseY - y) / height;
    camera_cible[2] += 10. * (mouseY - y) / height;

    //vers la gauche / droite
    camera_pos[0] += 10. * (mouseX - x) / width;
    camera_cible[0] += 10. * (mouseX - x) / width;
  }

    mouseX = x;
    mouseY = y;
}

void vBitmapOutput(int x, int y, char *string, void *font)
{
	int len,i; // len donne la longueur de la chaÃ®ne de caractÃ¨res

	glRasterPos2f(x,y);         // Positionne le premier caractÃ¨re de la chaÃ®ne
	len = (int) strlen(string); // Calcule la longueur de la chaÃ®ne
	for (i = 0; i < len; i++) glutBitmapCharacter(font,string[i]); // Affiche chaque caractÃ¨re de la chaÃ®ne
}

void vStrokeOutput(GLfloat x, GLfloat y, char *string, void *font)
{
	char *p;

	glPushMatrix();	// glPushMatrix et glPopMatrix sont utilisÃ©es pour sauvegarder
			// et restaurer les systÃ¨mes de coordonnÃ©es non translates
	glTranslatef(x, y, 0); // Positionne le premier caractÃ¨re de la chaÃ®ne
	for (p = string; *p; p++) glutStrokeCharacter(font, *p); // Affiche chaque caractÃ¨re de la chaÃ®ne
	glPopMatrix();
}

