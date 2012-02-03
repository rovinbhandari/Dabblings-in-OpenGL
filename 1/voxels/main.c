/* Program to test the voxel library functions */


#include <voxel.h>

GLfloat lightpos[] =
{10.f, 10.f, 10.f, 1.f};
GLfloat lightcol[] =
{1.0,1.0,1,0};

void init (void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display (void)
{
	GLdouble eyex = 6.0;
	GLdouble eyey = 6.0;
	GLdouble eyez = 6.0;

   /* Clear stencile each time */
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   glLoadIdentity ();
   
   /* Set eye and viewing direction */
   gluLookAt (eyex, eyey, eyez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   GLfloat voxel_mat[] = 
   {0.f, 0.f, 1, 1};
   
	vlInit (0.1);
	
	/* Create a voxel */
	glPushMatrix ();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, voxel_mat);
	glTranslated (0,0,5);
   vlVoxel ();
   glPopMatrix ();

	/* Create a cube using voxelib */
   GLfloat cube_mat[] = 
   {0.3, 0.1f, 0.05f, 1};
	glPushMatrix ();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cube_mat);
	glTranslated (0,3,0);
   vlCube (4.0);
   glPopMatrix (); 

	/* Create a cylinder using voxelib */
	GLfloat cylinder_mat[] = 
   {0.3, 0.2, 0.2f, 1};
	glPushMatrix ();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cylinder_mat);
	glTranslated (3.5,0,0);
	vlInit (0.06);
   vlCylinder (30.0, 70.0);
   glPopMatrix ();

	/* Create a sphere using voxelib */
	GLfloat sphere_mat[] = 
   {0.2, 0.5, 0.5f, 1};
	glPushMatrix ();
//	vlInit (0.01);
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, sphere_mat);
   vlSphere (44.0);
   glPopMatrix ();



	glutSwapBuffers ();
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

int main (int argc, char **argv)
{
   glutInit (&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (750, 750);               // TODO : Reference
   glutCreateWindow (argv[0]);                  // TODO : Reference
   init ();

   /* Set the display function */
   glutDisplayFunc (&display);

   /* Set the reshape function */
   glutReshapeFunc (&reshape);

   /* Set the keyboard function */
   glutKeyboardFunc (&keyboard);
   
   glEnable(GL_CULL_FACE);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   glLightfv (GL_LIGHT0, GL_POSITION, lightpos);
   glLightfv (GL_LIGHT0, GL_AMBIENT, lightcol);
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

   
   glMatrixMode(GL_PROJECTION);
   glOrtho(-50., 50., -50., 50., -50., 50.);
   glMatrixMode(GL_MODELVIEW);

   glutMainLoop ();

   return 0;
}
