#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

#define EDGESIZE  1.00

GLdouble eyex = 8.4;
GLdouble eyey = 8.4;
GLdouble eyez = 8.4;

GLfloat viewangle;

static GLfloat lightgray[] =
{0.2, 0.2, 0.2, 1};
static GLfloat gray[] =
{0.5, 0.5, 0.5, 1};
static GLfloat darkgray[] =
{0.8, 0.8, 0.8, 1};

void keyboard(unsigned char key, int x, int y)
{
   switch(key)
   {
      case 27: exit(0);
   }
}

void init(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
}

void display(void)
{
   /* clear stencil each time */
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   glLoadIdentity();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, lightgray);

   gluLookAt (eyex, eyey, eyez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   glPushMatrix();
   //glRotatef(viewangle, 0.f, 1.f, 0.f);
 
   //glEnable(GL_DEPTH_TEST);
   glutSolidCube(EDGESIZE);
   //glDisable(GL_DEPTH_TEST);

   glPopMatrix();
   glutSwapBuffers();
   
   glFlush();
}

int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(500, 500);               // TODO : Reference
   glutCreateWindow(argv[0]);                  // TODO : Reference
   init();

   /* Set the display function */
   glutDisplayFunc(&display);

   /* Set the keyboard function */
   glutKeyboardFunc(&keyboard);

/*
   GLUquadricObj *sphere;
   glEnable(GL_CULL_FACE);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   glLightfv (GL_LIGHT0, GL_POSITION, lightpos);
   glLightfv (GL_LIGHT0, GL_AMBIENT, lightcol);
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

   // make display lists for sphere and cone; for efficiency

   glNewList(1, GL_COMPILE);
   sphere = gluNewQuadric();
   //glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 100);
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, sphere_mat);
   gluSphere(sphere, 1.f, 100, 100);
   gluDeleteQuadric(sphere);
   glEndList();
*/
   
   glMatrixMode(GL_PROJECTION);
   glOrtho(-50., 50., -50., 50., -50., 50.);
   glMatrixMode(GL_MODELVIEW);

   glutMainLoop ();

   return 0;
}
