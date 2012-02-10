#include <blockworld.h>
#include <stdio.h>

GLfloat lightpos[] =
{100.f, 100.f, 100.f, 1.f};
GLfloat light_diffuse[] =
{1, 1, 1, 1};
GLfloat lightcol[] =
{1.0,1.0,1,0};

int opt, nopts = 3;

GLdouble eyex = 11.0;
GLdouble eyey = 11.0;
GLdouble eyez = 11.0;
   
void init(void);
void init2(void);
void keyboard(unsigned char, int, int);
void reshape(int, int);

void display (void)
{
   /* Clear stencile each time */
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   glLoadIdentity ();
   
   /* Set eye and viewing direction */
   gluLookAt(eyex, eyey, eyez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   GLfloat texture_cubelet[] = {0.3f, 0.2f, 0.1f, 1};
   GLfloat texture_cubelet2[] = {0.6f, 0.2f, 0.7f, 1};
   GLfloat texture_cube[] = {0.3, 0.1f, 0.05f, 1};
   GLfloat texture_cuboid[] = {0.3, 0.7f, 0.05f, 1};
   
   switch(opt)
   {
      case 0:
         // Create a cubelet 
         bwCubeletInit_gl(1);
         glPushMatrix();
         glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture_cubelet);
         bwCubelet_gl();
         glPopMatrix();
         bwCubeletInit_gl(5);
         glPushMatrix();
         glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture_cubelet2);
         bwTranslate(0, 0, -6);
         bwCubelet_gl();
         glPopMatrix();
         break;
   
      case 1:
      	// Create a cube 
      	glPushMatrix();
         glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture_cube);
      	bwTranslate(0, 1.8, 0);
         bwCubeSolid_gllen(7);
         glPopMatrix();
         break;

      case 2:
         // Create a cuboid
      	glPushMatrix();
         glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture_cuboid);
      	bwTranslate(0, 0.5, 0);
         bwCuboidSolid_gllen(4.0, 3.0, 5.0);
         glPopMatrix();
         break;
   }

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

void init2(void)
{
   /* Enable a single OpenGL light. */
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  /* Use depth buffering for hidden surface elimination. */
  glEnable(GL_DEPTH_TEST);

  /* Setup the view of the cube. */
  glMatrixMode(GL_PROJECTION);
  gluPerspective( /* field of view in degree */ 40.0,
    /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 10.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
    0.0, 0.0, 0.0,      /* center is at (0,0,0) */
    0.0, 1.0, 0.);      /* up is in positive Y direction */

  
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

