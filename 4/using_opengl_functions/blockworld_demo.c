#include <blockworld.h>

GLfloat lightpos[] = {10.f, 16.f, 10.f, 1.f};
GLfloat light_diffuse[] = {1, 1, 1, 1};

int opt, nopts = 5;

GLdouble eyex = 10;
GLdouble eyey = 6;
GLdouble eyez = 10;

// TODO: extend the 2d rotation of eye to 3d
#define PI 3.14d
GLdouble angle = PI / 180.0d * 45.0d;
const double root2 = sqrt(2);

void keyboard(unsigned char, int, int);
void reshape(int, int);

static GLfloat textureAhole[] = {0, 0, 0, 1};
static GLfloat textureA[] = {0.84, 0.84, 0, 1};
static GLfloat textureB1[] = {0.84, 0, 0, 1};
static GLfloat textureB2[] = {0, 0.84, 0, 1};
static GLfloat textureB3[] = {0, 0, 0.84, 1};

#define DELTA 0.002
GLboolean maketophole, makebothole;
void renderA()
{
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, textureA);
	bwCuboid(5, 5, 3);
	if(maketophole)
	{
		glPushMatrix();
	   	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, textureAhole);
		glTranslated(2, 3, 2);
		bwCuboid(1, 1, DELTA);
		glPopMatrix();
	}
	if(makebothole)
	{
		glPushMatrix();
	   	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, textureAhole);
		glTranslated(2, -DELTA, 2);
		bwCuboid(1, 1, DELTA);
		glPopMatrix();
	}
	glPopMatrix();
}

void renderB()
{
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, textureB1);
	glTranslated(0, -DELTA, 0);
	bwCuboid(1, 1, 3 + DELTA);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, textureB2);
	glTranslated(0, 3, 0);
	bwCuboid(1, 1, 3);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, textureB3);
	glTranslated(0, 6, 0);
	bwCuboid(1, 1, 3 + DELTA);
	glPopMatrix();
}
	

void display (void)
{   
   /* Clear stencile each time */
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   glLoadIdentity ();
   
	eyez = 10 * root2 * cos(angle);
	eyex = 10 * root2 * sin(angle);

   /* Set eye and viewing direction */
   gluLookAt(eyex, eyey, eyez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);


   switch(opt)
   {
      case 0:
        	glPushMatrix();
		glTranslated(6, -3, -1);
		renderB();
		glPopMatrix();
		maketophole = GL_TRUE;
		makebothole = GL_TRUE;
	break;
      case 1:
        	glPushMatrix();
		glTranslated(2, 3, 2);
		renderB();
		glPopMatrix();
		maketophole = GL_FALSE;
		makebothole = GL_TRUE;
	break;
      case 2:
        	glPushMatrix();
		glTranslated(2, 0, 2);
		renderB();
		glPopMatrix();
		maketophole = GL_FALSE;
		makebothole = GL_FALSE;
	break;
      case 3:
        	glPushMatrix();
		glTranslated(2, -3, 2);
		renderB();
		glPopMatrix();
		maketophole = GL_FALSE;
		makebothole = GL_FALSE;
	break;
      case 4:
        	glPushMatrix();
		glTranslated(2, -6, 2);
		renderB();
		glPopMatrix();
		maketophole = GL_FALSE;
		makebothole = GL_FALSE;
	break;
   }
	renderA(GL_TRUE, GL_TRUE);

   glutSwapBuffers();
}

void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   
   glShadeModel (GL_FLAT);
   
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
   glutInitWindowSize (950, 750);
   glutCreateWindow("using opengl functions");
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
	case 's':
	case 'S':
		eyey++;
		break;
	case 'x':
	case 'X':
		eyey--;
		break;
      default:
         opt = (opt + 1) % nopts;
         break;
   }
		glutPostRedisplay();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-2.0, 2.0, -2.0, 2.0, 1.5, 20.0);
   glMatrixMode (GL_MODELVIEW);
}

