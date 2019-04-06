#include <GL/glut.h>
#include <iostream>
#include <vector>

#include "ObjParser.h"
#include "Objet3D.h"


using namespace std;

//Ligne de commande de compilation
//g++ monPremierEssai.cpp -lGL -lglut -o monPremierEssai

	vector<Objet3D> objets;
	vector<Objet3D>::iterator it;
	int angle;

void initLight(void);
void idle(void);
void Reshape(int w, int h);
void render(void);
void keyboard(unsigned char c, int x, int y);
void mouse(int button, int state, int x, int y);

int main(int argc, char** argv) {

	ObjParser * parser = new ObjParser();

	angle = -1.0;
	float valZoom = 0.0;

	// Pour un écran Widescreen ratio d'aspect = 16:9
	long width = 800;
	long height = 450;
	float zNear = 0.1;
	float zFar = 50.0;
	float zoomFactor = 1.0;


	if (argv[1] != NULL) {
		printf("Lecture du fichier... \t %s\n", argv[1]);
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
	gluPerspective (50.0*zoomFactor, (float)width/(float)height, zNear, zFar);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	
	glMatrixMode(GL_MODELVIEW);

  initLight();
	gluLookAt(0.0, 6.0, 6.0, 0.0, 0.0, 0.0, 0.0 , 1.0, 0.0);
  

  glutDisplayFunc(render);
  glutIdleFunc(idle);
	//glutReshapeFunc(Reshape);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);

  glutMainLoop();
}


void initLight(void) 
{
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

void idle(void) {
	glutPostRedisplay();
	glutSwapBuffers();
}

void render(void) {
 	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glRotatef(angle,0.0,1.0,0.0);

	for(it = objets.begin(); it != objets.end(); it++) {
		it->dessiner();
	}


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



