#include <blockworld.h>

GLfloat lightpos[] =
{100.f, 100.f, 100.f, 1.f};
GLfloat light_diffuse[] =
{1, 1, 1, 1};
GLfloat lightcol[] =
{1.0,1.0,1,0};

void init(void);
void init2(void);
void keyboard(unsigned char, int, int);
void reshape(int, int);

void display (void)
{
	GLdouble eyex = 6.0;
   GLdouble eyey = 6.0;
   GLdouble eyez = 6.0;
   
   /* Clear stencile each time */
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   glLoadIdentity ();
   
   /* Set eye and viewing direction */
   gluLookAt(eyex, eyey, eyez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   /*
   // Create a cubelet 
	GLfloat texture_cubelet[] = {0.3f, 0.2f, 0.1f, 1};
   bwInit(1);
   glPushMatrix();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture_cubelet);
	bwTranslate(4, 0, 0);
   bwCubelet_glut();
   glPopMatrix();
   glPushMatrix();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture_cubelet);
	bwTranslate(0, 0, 4);
   bwCubelet_gl();
   glPopMatrix();
   */
   
	// Create a cuboid 
   GLfloat texture_cuboid[] = {0.3, 0.1f, 0.05f, 1};
   //bwCubeletInit_gl(1);
	glPushMatrix();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture_cuboid);
	bwTranslate(0, 1.8, 0);
   bwCuboidHollow_units(14.0, 6.0, 5.0);
   glPopMatrix();
   
   
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
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (750, 750);               // TODO : Reference
   glutCreateWindow (argv[0]);                  // TODO : Reference
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

