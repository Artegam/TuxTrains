/* Auteur: Nicolas JANEY               */
/* nicolas.janey@univ-fcomte.fr        */
/* Avril 2001                          */
/* Illustration de l'utilisation       */
/* de polices de caracteres avec GLUt  */

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

void bitmap_output(int x,int y,char *string,void *font) {
  int len,i;
  glRasterPos2f(x,y);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font,string[i]); }
}

void stroke_output(GLfloat x,GLfloat y,char *format,...) {
  va_list args;
  char buffer[200],*p;
  va_start(args,format);
  vsprintf(buffer,format,args);
  va_end(args);
  glPushMatrix();
  glTranslatef(x,y,0);
  glScalef(0.005F,0.005F,0.005F);
  for ( p = buffer ; *p ; p++ )
    glutStrokeCharacter(GLUT_STROKE_ROMAN,*p);
  glPopMatrix();
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  bitmap_output(10,35,"Ecrit avec une fonte bitmap GLUt.",GLUT_BITMAP_TIMES_ROMAN_24);
  bitmap_output(30,210,"Du texte en taille 9 par 15.",GLUT_BITMAP_9_BY_15);
  bitmap_output(70,240,"Une autre police : Helvetica.",GLUT_BITMAP_HELVETICA_18);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluPerspective(40.0,1.0,0.1,20.0);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  gluLookAt(0.0,0.0,4.0,0.0,0.0,0.0,0.0,1.0,0.);
  glPushMatrix();
  glTranslatef(0,0,-4);
  glRotatef(50,0,1,0);
  stroke_output(-3.0F,0.5F,"Ceci est ecrit en perspective");
  stroke_output(-2.7F,-0.5F,"avec une police vectorielle.");
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glFlush();
  glutSwapBuffers();
}

void reshape(int w,int h) {
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0,w,0,h);
  glScalef(1,-1,1);
  glTranslatef(0,-h,0);
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
  glutInitWindowSize(350,250);
  glutCreateWindow("Polices de caractères en GLUt");
  glClearColor(1.0,1.0,1.0,1.0);
  glColor3f(0,0,0);
  glLineWidth(3.0);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return(0);
}
