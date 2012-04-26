#include <BresenhamAlgorithm.hpp>
#include <pipelineFunctions.h>
#include <iostream>
#include <Cuboid.h>

GLfloat lightpos[] = {5.f, 12.f, 3.f, 1.f};
GLfloat light_diffuse[] = {1, 1, 1, 1};

int opt, nopts = 2, val, nvals = 3;

GLdouble eyex = 0;
GLdouble eyey = 0;
GLdouble eyez = 10;
 
#define PI 3.14d
#define TOLERANCE_COLOR 0.1

GLdouble angle = PI / 180.0d * 45.0d;
GLdouble pos = 0;

void keyboard(unsigned char, int, int);
void reshape(int, int);

double eyePosition[3];
double intensityAmbient[]  = {0.9, 0.9, 0.9};
double lightSource[3];
double intensitySource[3];

static const double root2 = sqrt (2);

void glEnable2D()
{
  int vPort[4];

   glGetIntegerv(GL_VIEWPORT, vPort);

   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();

   glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
   std::cerr << "vPort : " << vPort[2] << ", " << vPort[3] << "\n";
   glDisable(GL_DEPTH_TEST);
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
}

void glDisable2D()
{
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();   
   glMatrixMode(GL_MODELVIEW);
   glPopMatrix(); 
}

void display (void)
{   
   /* Clear stencile each time */
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   glLoadIdentity ();

	fprintf(stderr, "eyex = %lf\neyey = %lf\neyez = %lf\n\n", eyex, eyey, eyez);
  std::cerr << "Case " << opt << "\n";

//	eyePosition[0] = eyex;
//	eyePosition[1] = eyey;
//	eyePosition[2] = eyez;

   /* Set eye and viewing direction */
  gluLookAt(eyex, eyey, eyez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	Pt2D A(0, 0), B(3, 3);
	Color C (32.0d/255, 178.0/255, 0.0);

  Color c;
  list<Polygon> l, ltmp;
  Cuboid *cuboid, *cuboid2, *cuboid3, *cuboid4;
	map<Pt2D,Color> depth;
  map<Pt2D,Color>::iterator itr;
//  double eyez = 10 * root2 * cos(angle);
//	double eyex = 10 * root2 * sin(angle);
  Pt3D eye (0, 0, 10);
//  eye.x = 10 * root2 * cos(angle);
//  eye.z = 10 * root2 * sin(angle);
  Vector up (0, 1, 0);
  Vector viewNormal (0, 0, 1);
 switch(opt)
   {
      case 1:
    		BresenhamLine(A, B, C);
        break;
      case 0:
      
        cuboid = new Cuboid(Pt3D(-1, 0, 0), 3, 5, 3, Color (1, 1, 0) );
        switch (val)
        {
          case 0:
            cuboid2 = new Cuboid(Pt3D(0, 6, 0), 1, 1, 3, Color (1, 0 , 0));
            cuboid3 = new Cuboid(Pt3D(0, 3, 0), 1, 1, 3, Color (0, 1 , 0));
            cuboid4 = new Cuboid(Pt3D(0, 0, 0), 1, 1, 3, Color (0, 0 , 1));
            break;
          case 1:
            cuboid2 = new Cuboid(Pt3D(0, 3, 0), 1, 1, 3, Color (1, 0 , 0));
            cuboid3 = new Cuboid(Pt3D(0, 0, 0), 1, 1, 3, Color (0, 1 , 0));
            cuboid4 = new Cuboid(Pt3D(0, -3, 0), 1, 1, 3, Color (0, 0 , 1));
            break;

          case 2:
            cuboid2 = new Cuboid(Pt3D(0, 0, 0), 1, 1, 3, Color (1, 0 , 0));
            cuboid3 = new Cuboid(Pt3D(0, -3, 0), 1, 1, 3, Color (0, 1 , 0));
            cuboid4 = new Cuboid(Pt3D(0, -6, 0), 1, 1, 3, Color (0, 0 , 1));
            break;
        }
        cuboid->applyViewTransformation (eye, up, viewNormal);
        cuboid2->applyViewTransformation (eye, up, viewNormal);
        cuboid3->applyViewTransformation (eye, up, viewNormal);
        cuboid4->applyViewTransformation (eye, up, viewNormal);
        l = cuboid->toPolygonList();
        ltmp = cuboid2->toPolygonList();
        l.insert (l.end(), ltmp.begin(), ltmp.end());
        ltmp = cuboid3->toPolygonList();
        l.insert (l.end(), ltmp.begin(), ltmp.end());
        ltmp = cuboid4->toPolygonList();
        l.insert (l.end(), ltmp.begin(), ltmp.end());
        
        std::cerr << "size of polygon list " << l.size() << "\n";
        depth = depthBufferMethod (l);
//        glEnable2D();
        for (itr = depth.begin(); itr != depth.end(); itr++)
        {
          glColor3f (itr->second.r, itr->second.g, itr->second.b);
          glBegin(GL_POINTS);
          glVertex2f (itr->first.x, itr->first.y);
/*          std::cerr << itr->first.x  << "," << itr->first.y << "  -- "
                  << itr->second.r << ","
                  << itr->second.g << ","
                  << itr->second.b << "\n"; */
          glEnd();
        }
//        glDisable2D();
        std::cerr << "Done";
//        std::cerr << glGet(GL_POINT_SIZE_RANGE);
        delete cuboid;
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
		angle += PI / 180.0d * 10.0d;
		break;

	case 'z':
	case 'Z':
		angle -= PI / 180.0d * 10.0d;
		break;

      default:
//         opt = (opt + 1) % nopts;
           val = (val + 1) % nvals;
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
   glFrustum (-2.0, 2.0, -2.0, 2.0, 1.5, 20.0);
//   Frustum (-1.0, 1.0, 1.0, -1.0, 1.5, 20.0);
//   Frustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
   glMatrixMode (GL_MODELVIEW);
}

