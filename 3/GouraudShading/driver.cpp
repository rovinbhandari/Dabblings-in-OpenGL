#include <Cuboid.hpp>
#include <GouraudShading.hpp>
#include <GL/glut.h>
#include <GL/gl.h>
#include <cstdio>

GLfloat lightpos[] = {5.f, 12.f, 3.f, 1.f};
GLfloat light_diffuse[] = {1, 1, 1, 1};

int opt, nopts = 1;

GLdouble eyex = 10;
GLdouble eyey = 10;
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
	cs.setAmbientCoefficient(0.4);
	cs.setDiffusionCoefficient(0.67);
	cs.setSpecularCoefficient(0.99);
	cs.setSpecularParameter(84);
	fprintf(stderr, "***\nK_a = %lf\nK_d = %lf\nK_s = %lf\nN_s = %lf\n\n", cs.getAmbientCoefficient(), cs.getDiffusionCoefficient(), cs.getSpecularCoefficient(), cs.getSpecularParameter());
	cs.Translate(1, 2, 3);
	double cubeCol[] = {0.8, 0.4, 0};
	cs.SetColour(cubeCol);

	double eyePosition[]   = {eyex, eyey, eyez};
	double intensityAmbient[]  = {0.9, 0.9, 0.9};
	double lightSource[3];
	lightSource[0] = lightpos[0];
	lightSource[1] = lightpos[1];
	lightSource[2] = lightpos[2];
	double intensitySource[3];
	intensitySource[0] = light_diffuse[0];
	intensitySource[1] = light_diffuse[1];
	intensitySource[2] = light_diffuse[2];
	
  	for(int face = 0; face < 6; face++)
		cs.constructFace (face, lightSource, eyePosition, intensityAmbient, intensitySource);

        break;
   }
   glutSwapBuffers();
}

void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   
   glShadeModel (GL_SMOOTH);
   
   //glLightfv (GL_LIGHT0, GL_POSITION, lightpos);
   //glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
   //glEnable(GL_LIGHTING);
   //glEnable(GL_LIGHT0);
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

