#include <blockworld.h>
#include <stdio.h>

GLfloat lightpos1[] =
{110.f, 111.f, 110.f, 1.f};
GLfloat light_diffuse1[] =
{1, 1, 1, 1};
GLfloat lightpos2[] =
{-90.f, -95.f, -11.f, 1.f};
GLfloat light_diffuse2[] =
{1, 1, 1, 1};

int opt, nopts = 2;

GLdouble eyex = 11.0;
GLdouble eyey = 11.0;
GLdouble eyez = 11.0;
   
void init(void);
void keyboard(unsigned char, int, int);
void reshape(int, int);

void display (void)
{
   /* Clear stencile each time */
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   glLoadIdentity ();
   
   /* Set eye and viewing direction */
   gluLookAt(eyex, eyey, eyez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   GLfloat texture_cube[] = {0.9, 0.9f, 0.0f, 1};
   GLfloat texture_cuboid[] = {0.0, 0.0f, 0.0f, 1};
   
   switch(opt)
   {
      case 0:
         // Create a cuboid 
         //glPushMatrix();
         glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture_cuboid);
         //bwTranslate(0, 4, 1.2);
	 bwCuboid(5, 3.2, 6.3);
         //glPopMatrix();
         glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture_cube);
         bwCuboid(8, 5.2, 1.3);
         break;
   
      case 1:
      	// Create a cube
      	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture_cube);
      	bwTranslate(0, 0, 0);
        bwCube(7);
        glPopMatrix();
        break;
   }

   glutSwapBuffers();
}

void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   
   glShadeModel (GL_FLAT);
   
   glLightfv (GL_LIGHT0, GL_POSITION, lightpos1);
   glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse1);
   
   glLightfv (GL_LIGHT1, GL_POSITION, lightpos2);
   glLightfv (GL_LIGHT1, GL_DIFFUSE, light_diffuse2);
      
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);
   glEnable(GL_DEPTH_TEST);

   
   glMatrixMode(GL_PROJECTION);
   glOrtho(-50., 50., -50., 50., -50., 50.);
   glMatrixMode(GL_MODELVIEW);
}

int main (int argc, char **argv)
{
   glutInit (&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowPosition(300, 300);
   glutInitWindowSize (750, 750);
   glutCreateWindow("BL[]CKW[]RLD");
   init();

   /* Set the display function */
   glutDisplayFunc (&display);

   /* Set the reshape function */
   glutReshapeFunc (&reshape);

   /* Set the keyboard function */
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

