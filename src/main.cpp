#include <GL/glut.h>
#include <iostream>
#include <vector>

#include "Parser/ObjParser.h"
#include "Parser/MatParser.h"
#include "Objet3D.h"

using namespace std;

//Ligne de commande de compilation
//g++ monPremierEssai.cpp -lGL -lglut -o monPremierEssai

	vector<Objet3D> objets;
	vector<Objet3D>::iterator it;
  map<string, Material> materials;
	int angle;
  GLfloat anim =0;
  static int frame = 0;
  static int current_time = 0;
  static int last_time = 0;
  static double fps = 0.0; //Le nb de fps

void initLight(void);
void idle(void);
void Reshape(int w, int h);
void render(void);
void keyboard(unsigned char c, int x, int y);
void mouse(int button, int state, int x, int y);

int main(int argc, char** argv) {

	ObjParser * parser;
  MatParser materiaux;

	angle = -1.0;
	//float valZoom = 0.0;

	// Pour un écran Widescreen ratio d'aspect = 16:9
	long width = 800;
	long height = 450;
	float zNear = 0.1;
	float zFar = 50.0;
	float zoomFactor = 1.0;


	if (argv[1] != NULL) {
		printf("Lecture du fichier... \t %s\n", argv[1]);
    materials = materiaux.readFile(argv[2]);
    parser = new ObjParser(materials);
		objets = parser->readFile(argv[1]);
	} else {
		printf("Veuillez passer en argument le nom du fichier obj (exemple: ./essai3D ./obj/jaguard.obj\n");
		return 0;
	}


	parser->~ObjParser();

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

  //Initialisation des objets (chargement dans la carte graphique pour le rendu
	for(it = objets.begin(); it != objets.end(); it++) {
		it->init();
	}

  glutDisplayFunc(render);
  glutIdleFunc(idle);
	//glutReshapeFunc(Reshape);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);

  glutMainLoop();
}


void initLight(void)
{

  printf("LIGHT Initialisation()....\n");


  //LIGHT0
   GLfloat lightpos[] = {2.0, 2.0, 2.0, 0.0};
   GLfloat lightdiffuse[] = {0.0, 0.0, 2.0, 0.0};
   GLfloat lightspecular[] = {0.0, 0.0, 2.0, 0.0};

   glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, lightdiffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, lightspecular);

   //LIGHT1
   GLfloat lightpos1[] = {0.0, 15.0, 0.0, 0.0};
   GLfloat lightdiffuse1[] = {2.0, 2.0, 2.0, 0.0};
   GLfloat lightspecular1[] = {2.0, 2.0, 2.0, 0.0};

   glLightfv(GL_LIGHT1, GL_POSITION, lightpos1);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, lightdiffuse1);
   glLightfv(GL_LIGHT1, GL_SPECULAR, lightspecular1);



   glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);

// FIN POUR LES TESTS DE LUMIERE
  printf("Fin de LIGHT Initialisation...\n");


}

void idle(void) {

  frame++;
  current_time = glutGet(GLUT_ELAPSED_TIME);

  if(current_time - last_time > 1000) {
    fps = frame * 1000.0 / (current_time - last_time);
		printf("FPS : %f\n", fps);
    last_time = current_time;
    frame = 0;
  }

	glutPostRedisplay();
	glutSwapBuffers();
}

void render(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //glRotatef(angle,0.0,1.0,0.0);

	for(it = objets.begin(); it != objets.end(); it++) {
		it->dessiner();
	}

  glRotatef(angle,0.0,1.0,0.0);

//Pour symbolyser la lumiÃ¨re du soleil
  GLfloat es[4] = {0.8f, 0.8f, 0.8f, 1.0f};
  glMaterialfv(GL_FRONT, GL_EMISSION, es);
  GLfloat cs[3] = {0.0f, 15.0f, 0.0f};
  glTranslatef(cs[0], cs[1], cs[2]);
  glutSolidSphere(0.25, 6, 6);
  glTranslatef(0-cs[0], 0-cs[1], 0-cs[2]);

  //Pour symboliser la lumiÃ¨re bleue qui se dÃ©place
  GLfloat e[4] = {0.0f, 0.0f, 0.8f, 1.0f};
  glMaterialfv(GL_FRONT, GL_EMISSION, e);

  anim += 0.5;
  if (anim == 10.0) anim = -10.0;

  GLfloat c[3] = {2.0f+anim, 2.0f, 2.0f};
  glTranslatef(c[0], c[1], c[2]);
  glutSolidCube(0.5);

  GLfloat lightpos[] = {c[0], c[1], c[2], 1.0};
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
  glTranslatef(0-c[0], 0-c[1], 0-c[2]);


  glutSwapBuffers();
	glFlush();
}

void Reshape(int w, int h)
{
		glViewport( 0, 0, (GLint)w, (GLint)h );
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		glFrustum( -1.0, 1.0, -1.0, 1.0, 1.5, 100.0);
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
}

void keyboard(unsigned char c, int x, int y){
  // ASCH - 29/09/2014 - La touche 27 est la touche echap
  if (c == 27) {
    exit(0);
  }

}

void mouse(int button, int state, int x, int y){
  if(button == GLUT_RIGHT_BUTTON) {
    exit(0);
  }
}



