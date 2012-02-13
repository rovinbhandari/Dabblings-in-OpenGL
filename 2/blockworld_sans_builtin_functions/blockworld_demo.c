#include <blockworld.h>
#include <blockworld_complex_figures.h>

GLfloat lightpos1[] = {110.f, 16.f, 10.f, 1.f};
GLfloat lightpos2[] = {-90.f, -95.f, -11.f, 1.f};
GLfloat light_diffuse1[] = {0.8, 0.8, 0.8, 1};
GLfloat light_diffuse2[] = {1, 1, 1, 1};

int opt, nopts = 4;

GLdouble eyex = 10;
GLdouble eyey = 8;
GLdouble eyez = 10;
 
GLint angle = 45;
GLdouble pos = 0;

void keyboard(unsigned char, int, int);
void reshape(int, int);

void display (void)
{   
   opt = 4;
   /* Clear stencile each time */
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   glLoadIdentity ();
   
   /* Set eye and viewing direction */
   gluLookAt(eyex, eyey, eyez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   GLfloat texture1[] = {0.3, 0.06f, 0.33f, 1};
   GLfloat texture2[] = {0.4, 0.1f, 0.1f, 1};
   
   switch(opt)
   {
      case 0:
        // Create a house
        bwHouse ();
        break;

      case 1:
        // Create Tree
        bwScale(0.2, 0.2, 0.2);
        //bwRotate(-45, 1, 0, -1);
        bwTranslate(-1, -10, -1);
        bwTree();
        break;
      
      case 3:
        // Create the whole scene
        //  Tree
        glPushMatrix ();
        bwTranslate (2, -7.5, -3.0); 
        bwScale (0.18, 0.18, 0.18);
        bwRotate (-45, 0, 1, 0);
        bwTree();
        glPopMatrix ();
        //  House
        glPushMatrix ();
        bwTranslate (-10, -3, 1);
        bwScale (1.1, 1.3, 1.1);
        bwRotate (20, 0, 1, 0); 
        bwHouse ();
        glPopMatrix ();
        //  Dog
        bwTranslate (0,-5,6);
        bwRotate (30, 0, 1, 0);
        bwScale (0.3, 0.3, 0.3);
        bwDog ();  
        break;
      
      case 2:
        //Create a character
        bwDog();
        break;
      case 4:
        //Create a road
        bwTranslate(-2, 0, 3);
        bwRoad (15, 3, 0.2);
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
   glOrtho(-200., 200., -150., 150., -150., 150.);
   glMatrixMode(GL_MODELVIEW);

   srand(time(NULL));
}

int main (int argc, char **argv)
{
   glutInit (&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowPosition(300, 300);
   glutInitWindowSize (950, 750);
   glutCreateWindow("BL[]CKW[]RLD");
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
      case 'a' :
        angle = (angle + 2);
        glutPostRedisplay ();
        break;
      case 'z':
        angle = (angle - 2);
        glutPostRedisplay ();
        break;
      case 'd' :
        pos = (pos + 0.5);
        glutPostRedisplay ();
        break;
      case 's' :
        pos = (pos - 0.5);
        glutPostRedisplay ();
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

