#include <Cuboid.hpp>
#include <GouraudShading.hpp>
#include <GL/glut.h>
#include <GL/gl.h>
#include <cstdio>

GLfloat lightpos[] = {110.f, 16.f, 10.f, 1.f};
GLfloat light_diffuse[] = {1, 1, 1, 1};

int opt, nopts = 1;

GLdouble eyex = 10;
GLdouble eyey = 8;
GLdouble eyez = 10;
 
GLint angle = 45;
GLdouble pos = 0;

void keyboard(unsigned char, int, int);
void reshape(int, int);

void display (void)
{   
   /* Clear stencile each time */
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   glLoadIdentity ();
   
   /* Set eye and viewing direction */
   gluLookAt(eyex, eyey, eyez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   switch(opt)
   {
      case 0:
//      glutSolidTorus (3, 6, 8, 100);
 	CD c = { 4, 4, 4};
	CuboidShading cs(c);

	double normals[3][3];
	double avgNormal[3];

	cs.GetNormals(0, normals);

	double vertex[3];
	cs.GetVertex(0, vertex);

	cs.avgNormal (normals, avgNormal);
	double eyePosition[]   = {eyex, eyey, eyez};
	double intensityAmbient[]  = {0.5, 0.5, 0.5};
	double lightSource[]   = {110.f, 16.f, 10.f};
	double intensitySource[] = {1, 1, 1};
	
  fprintf (stderr, "About to calc\n");
  cs.constructFace (0, lightSource, eyePosition, intensityAmbient, intensitySource);


	
	
        break;
   }
   glutSwapBuffers();
}

void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   
   glShadeModel (GL_SMOOTH);
   
   glLightfv (GL_LIGHT0, GL_POSITION, lightpos);
   glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);

   
   glMatrixMode(GL_PROJECTION);
   glOrtho(-200., 200., -150., 150., -150., 150.);
   glMatrixMode(GL_MODELVIEW);

}

int main (int argc, char **argv)
{
   glutInit (&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowPosition(300, 300);
   glutInitWindowSize (900, 700);
   glutCreateWindow("Gouraud Shading");
   init();
   glutDisplayFunc (&display);
   glutReshapeFunc (&reshape);
   glutKeyboardFunc (&keyboard);
   glutMainLoop ();
   return 0;
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key)
   {
      case 27 :
         exit (0);
         break;
      default:
         opt = (opt + 1) % nopts;
			glutPostRedisplay();
         break;
   }
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
   glMatrixMode (GL_MODELVIEW);
}

