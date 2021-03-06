#include <Cuboid.hpp>
#include <GouraudShading.hpp>
#include <GL/glut.h>
#include <GL/gl.h>
#include <cstdio>
#include <cmath>

GLfloat lightpos[] = {5.f, 12.f, 3.f, 1.f};
GLfloat light_diffuse[] = {1, 1, 1, 1};

int opt, nopts = 4;

GLdouble eyex = 10;
GLdouble eyey = 10;
GLdouble eyez = 10;
 
#define PI 3.14d

GLdouble angle = PI / 180.0d * 45.0d;
GLdouble pos = 0;

void keyboard(unsigned char, int, int);
void reshape(int, int);

double eyePosition[3];
double intensityAmbient[]  = {0.9, 0.9, 0.9};
double lightSource[3];
double intensitySource[3];
void renderCuboid(CD& cd, double ka, double kd, double ks, double ns, double tx, double ty, double tz, int ra, double rA, double sx, double sy, double sz, double col[]);


static const double root2 = sqrt (2);

void display (void)
{   
   /* Clear stencile each time */
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   glLoadIdentity ();
   
	eyez = 10 * root2 * cos(angle);
	eyex = 10 * root2 * sin(angle);

	fprintf(stderr, "eyex = %lf\neyey = %lf\neyez = %lf\n\n", eyex, eyey, eyez);

	eyePosition[0] = eyex;
	eyePosition[1] = eyey;
	eyePosition[2] = eyez;

   /* Set eye and viewing direction */
   gluLookAt(eyex, eyey, eyez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

 	CD cd = { 4, 4, 4};
	double cubeCol[] = {0.8, 0.4, 0};
	CD cdtrunk = {1, 5.5, 1};
	double coltrunk[] = {0.8, 0.4, 0.2};
	CD cdleaf = {1.5, 1.5, 1.5};
	double colleaf[] = {0.1, 0.7, 0.1};
	CD cdhouse1 = {5, 6, 4};
	double colhouse1[] = {0.5, 0.5, 0.35};
	CD cdhouse2 = {4, 1, 3};
	double colhouse2[] = {0.7, 0.1, 0.1};
	CD cdhouse3 = {3, 0.7, 2};
	CD cdhouse4 = {2, 4, 0.1};

   switch(opt)
   {
      case 0:

		renderCuboid(cd, 0.15, 0.4, 0.3, 84, 1, 2, 3, NONE, 0, 0, 0, 0, cubeCol);

        break;
	
	case 1:
		renderCuboid(cdtrunk, 0.15, 0.4, 0.3, 84, 4, -1, -1, NONE, 0, 0, 0, 0, coltrunk);
		
		renderCuboid(cdleaf, 0.15, 0.4, 0.3, 84, 5, 5, -1, NONE, 0, 0, 0, 0, colleaf);
		renderCuboid(cdleaf, 0.15, 0.4, 0.3, 84, 4, 5, 0, NONE, 0, 0, 0, 0, colleaf);
		renderCuboid(cdleaf, 0.15, 0.4, 0.3, 84, 5.5, 5, 0.5, NONE, 0, 0, 0, 0, colleaf);
		renderCuboid(cdleaf, 0.15, 0.7, 0.3, 84, 4.8, 6.6, -0.5, NONE, 0, 0, 0, 0, colleaf);
		/*
		renderCuboid(cdleaf, 0.15, 0.4, 0.3, 84, 4, -1, -1, NONE, 0, 0, 0, 0, colleaf);
		*/

	break;

	case 2:
		renderCuboid(cdhouse1, 0.5, 0.6, 0.3, 71, -4, -3, 0, NONE, 0, 0, 0, 0, colhouse1);
		renderCuboid(cdhouse2, 0.3, 0.6, 0.3, 71, -3.7, 3, 0.5, NONE, 0, 0, 0, 0, colhouse2);
		renderCuboid(cdhouse3, 0.3, 0.6, 0.3, 71, -3, 4, 1, NONE, 0, 0, 0, 0, colhouse2);
		renderCuboid(cdhouse4, 0.3, 0.6, 0.3, 48, -2.2, -3, 4, NONE, 0, 0, 0, 0, coltrunk);
	break;

	case 3:
		renderCuboid(cdtrunk, 0.15, 0.4, 0.3, 84, 4, -1, -1, NONE, 0, 0.7, 0.7, 0.7, coltrunk);
		renderCuboid(cdleaf, 0.15, 0.4, 0.3, 84, 5, 5, -1, NONE, 0, 0.7, 0.7, 0.7, colleaf);
		renderCuboid(cdleaf, 0.15, 0.4, 0.3, 84, 4, 5, 0, NONE, 0, 0.7, 0.7, 0.7, colleaf);
		renderCuboid(cdleaf, 0.15, 0.4, 0.3, 84, 5.5, 5, 0.5, NONE, 0, 0.7, 0.7, 0.7, colleaf);
		renderCuboid(cdleaf, 0.15, 0.7, 0.3, 84, 4.8, 6.6, -0.5, NONE, 0, 0.7, 0.7, 0.7, colleaf);
		
		renderCuboid(cdhouse1, 0.5, 0.6, 0.3, 71, -4, -3, 0, NONE, 0, 0, 0, 0, colhouse1);
		renderCuboid(cdhouse2, 0.3, 0.6, 0.3, 71, -3.7, 3, 0.5, NONE, 0, 0, 0, 0, colhouse2);
		renderCuboid(cdhouse3, 0.3, 0.6, 0.3, 71, -3, 4, 1, NONE, 0, 0, 0, 0, colhouse2);
		renderCuboid(cdhouse4, 0.3, 0.6, 0.3, 48, -2.2, -3, 4, NONE, 0, 0, 0, 0, coltrunk);
	break;

	default:
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

	lightSource[0] = lightpos[0];
	lightSource[1] = lightpos[1];
	lightSource[2] = lightpos[2];
	intensitySource[0] = light_diffuse[0];
	intensitySource[1] = light_diffuse[1];
	intensitySource[2] = light_diffuse[2];
}

#define EPSILON 0.0001

void renderCuboid(CD& cd, double ka, double kd, double ks, double ns, double tx, double ty, double tz, int ra, double rA, double sx, double sy, double sz, double col[])
{
	CuboidShading cs(cd);
	cs.setAmbientCoefficient(ka);
	cs.setDiffusionCoefficient(kd);
	cs.setSpecularCoefficient(ks);
	cs.setSpecularParameter(ns);
	fprintf(stderr, "***\nK_a = %lf\nK_d = %lf\nK_s = %lf\nN_s = %lf\n\n", cs.getAmbientCoefficient(), cs.getDiffusionCoefficient(), cs.getSpecularCoefficient(), cs.getSpecularParameter());
	if(fabs(tx) + fabs(ty) + fabs(tz) > EPSILON)
		cs.Translate(tx, ty, tz);
	if(ra != NONE && fabs(rA) > EPSILON)
		cs.Rotate(ra, rA);
	if(fabs(sx) + fabs(sy) + fabs(sz) > EPSILON)
		cs.Scale(sx, sy, sz);
	cs.SetColour(col);

  	for(int face = 0; face < 6; face++)
		cs.constructFace (face, lightSource, eyePosition, intensityAmbient, intensitySource);
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

	case 'a':
	case 'A':
		angle += PI / 180.0d * 20.0d;
		break;

	case 'z':
	case 'Z':
		angle -= PI / 180.0d * 20.0d;
		break;

      default:
         opt = (opt + 1) % nopts;
         break;
   }
			glutPostRedisplay();
}

void viewPort (int x, int y, double width, double height)
{
  GLfloat xmin, xmax, ymax, ymin, vmax, vmin, umax, umin;

  umin = x;
  umax = umin + width;

  vmin = y;
  vmax = vmin + height;

  xmin = 0;
  ymin = 0;
  xmax = 900;
  ymax = 700;


  glMatrixMode (GL_PROJECTION);
  glPushMatrix();
  glTranslatef (-xmin, -ymin, 0);
  glScalef ((umax - umin) / (xmax - xmin), (vmax - vmin) / (ymax - ymin), 1);
  glTranslatef (umin, vmin, 0);
  glPopMatrix();
}

void Frustum (double left, double right, double bottom, double top, double near, double far)
{
  double A = (right + left) / (right - left);
  double B = (top + bottom) / (top - bottom);
  double C = - (far + near) / (far - near);
  double D = -2 * far * near / (far - near);

  double E = 2 * near / (right - left);
  double F = 2 * near / (top - bottom);

  double matrix[] = {
                      E, 0, A, 0,
                      0, F, B, 0,
                      0, 0, C, D,
                      0, 0,-1, 0
                    };

  glMultTransposeMatrixd (matrix);                    
}

void reshape (int w, int h)
{
//   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   viewPort (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
//   Frustum (-1.0, 1.0, 1.0, -1.0, 1.5, 20.0);
   Frustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
   glMatrixMode (GL_MODELVIEW);
}

