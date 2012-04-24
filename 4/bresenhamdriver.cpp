#include <BresenhamAlgorithm.hpp>
#include <pipelineFunctions.h>
#include <iostream>

GLfloat lightpos[] = {5.f, 12.f, 3.f, 1.f};
GLfloat light_diffuse[] = {1, 1, 1, 1};

int opt, nopts = 2;

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

static const double root2 = sqrt (2);

void display (void)
{   
   /* Clear stencile each time */
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   glLoadIdentity ();
   
	eyez = 10 * root2 * cos(angle);
	eyex = 10 * root2 * sin(angle);

	fprintf(stderr, "eyex = %lf\neyey = %lf\neyez = %lf\n\n", eyex, eyey, eyez);
  std::cerr << "Case " << opt << "\n";

	eyePosition[0] = eyex;
	eyePosition[1] = eyey;
	eyePosition[2] = eyez;

   /* Set eye and viewing direction */
   gluLookAt(eyex, eyey, eyez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	Pt2D A(0, 0), B(4, 0);
	Color C = {32.0d/255, 178.0/255, 0.0, 1.0};

  vector<Pt3D> vertices;
	vertices.push_back(Pt3D(0,0,1));
	vertices.push_back(Pt3D(5,0,1));
	vertices.push_back(Pt3D(0,5,1));
	vertices.push_back(Pt3D(0,5,1));

  Polygon t (vertices, Vector (0,0,1));
  
  vertices.clear();
	vertices.push_back(Pt3D(0,0,2));
	vertices.push_back(Pt3D(3,0,2));
	vertices.push_back(Pt3D(3,3,2));
	vertices.push_back(Pt3D(0,3,2));
	Polygon u (vertices, Vector(0,0,1));
  Color c;
  list<Polygon> l;
	map<Pt2D,Color> depth;
  map<Pt2D,Color>::iterator itr;
 switch(opt)
   {
      case 0:
		BresenhamLine(A, B, C);

        break;
      case 1:
      
      std::cerr << "IN CASE 1\n";
      c.r = 1;
      c.g = 0;
      c.b = 0;
	
	  t.setColor (c);
	std::cerr << "Polygon 1 ready\n";
      
      c.r = 1;
      c.g = 1;
      c.b = 1;
	
  u.setColor (c);
	std::cerr << "Polygon 2 ready\n";
  
  l.clear();
	l.push_back(t);
	l.push_back(u);
  depth = depthBufferMethod (l);
	  for (itr = depth.begin(); itr != depth.end(); itr++)
  {
      glColor3f (itr->second.r, itr->second.g, itr->second.b);
      glBegin(GL_POINTS);
      glVertex2f (itr->first.x, itr->first.y);
/*      std::cerr << itr->first.x  << "," << itr->first.y << "  -- "
              << itr->second.r << ","
              << itr->second.g << ","
              << itr->second.b << "\n"; 
*/	    glEnd();
  }
    std::cerr << "Done";
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

