//#include <Cuboid.hpp>
//#include <GouraudShading.hpp>
#include <GL/glut.h>
#include <GL/gl.h>
#include <cstdio>
#include <cmath>

GLfloat lightpos[] = {5.f, 12.f, 3.f, 1.f};
GLfloat light_diffuse[] = {1, 1, 1, 1};

int opt, nopts = 1;

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

float absol(float a)
{
	if(a<0)return -a;
	return a;
}

#define INTERVAL1 0.01
#define INTERVAL2 0.0001

// m<-1, m=-1 -1<m<0 0<m<1,m=1,m>1,dx=0,dy=0
/* Bresenham line-drawing procedure */
void bresenhamline(float v[3], float e[3])
{	
	glColor3f (1.0, 0.0, 1.0);
	float dx = (e[0] - v[0]);  
	float dy = (e[1] - v[1]);
	float t[2];
	glBegin(GL_POINTS);

	if(dx == 0)
	{
		if (v[1] > e[1])
		{
			t[1] = e[1];
			e[1] = v[1];
		}
		else 
			t[1] = v[1];
		while (t[1]<=e[1])
		{
			glVertex2f(v[0], t[1]);
			t[1]=t[1]+INTERVAL1;//y++
		}
	}
	else if (dy == 0)
	 {
		if(v[0] > e[0])
		{
			t[0] = e[0];
			e[0] =v[0];
		}
		else 
			t[0] = v[0];
		while (t[0]<=e[0])
		{
			glVertex2f(t[0],v[1]);
			t[0]=t[0]+INTERVAL1;//x++;
		}
	 }
	 // |slope| < 1 
	 else if (absol(dy) < absol(dx))
	  { //printf("slope < 1 \n");
		float p = 2*(absol(dy)) - (absol(dy));
		float twoDy = 2*absol(dy), twoDyMinusDx = 2*(absol(dy)-absol(dx));

		// Determine which endpoint to use as start position.
		if (v[0] > e[0]) {
			t[0] = e[0];
			t[1] = e[1];
			e[0] = v[0]; 
		}
		else 
		{
			t[0]= v[0];
			t[1] = v[1];
		}
		glVertex2f(t[0],t[1]);
//printf("slope < 1 \n");
		while(t[0] < e[0])
		{
			t[0]+=INTERVAL2;//t[0]++;
			if (p < 0)
				p += twoDy;
			else  
			{
				if (dx * dy > 0)
					t[1]+=INTERVAL1;//t[1]++; // slope > 0 		
				else 
					t[1]-=INTERVAL1;//t[1]--;              // slope < 0
				p += twoDyMinusDx;
			}	
			glVertex2f(t[0],t[1]);
		}
	  }
	  // |slope| > 1
	  else if (absol(dy) > absol(dx))  
	  {//printf("slope > 1 \n");
		float p = 2*(absol(dx)) - (absol(dy));
		float twoDx = 2*absol(dx), twoDxMinusDy = 2*(absol(dx)-absol(dy));
		// Determine which endpoint to use as start position.
		if (v[1] > e[1]) {
			t[1] = e[1];
			t[0] = e[0];
			e[1] = v[1]; 
		}
		else {
			t[0] = v[0];
			t[1] = v[1];
		}
		glVertex2f(t[0],t[1]);

		while(t[1] < e[1])
		{
			t[1]=t[1]+INTERVAL2;//t[1]++;
			{
			
				if (p < 0)
					p += twoDx;
				else 
				{
					if (dx*dy>0)
						t[0]+=INTERVAL1;//t[0]++;
					else  
						t[0]-=INTERVAL1;//t[0]--;
					p += twoDxMinusDy;
				}	
			}
			glVertex2f(t[0],t[1]);
		}
	  }
	  // |slope|= 1
	  else if (absol(dx) == absol(dy))
	  {//printf("slope = 1 \n");
		if (v[0] > e[0]) 
		{
		   t[0] = e[0];
		   t[1] = e[1];
		   e[0] = v[0]; 
		}
		else 
		{
		   t[0] = v[0];
		   t[1] = v[1];
		}
		glVertex2f(t[0],t[1]);
		while(t[0] < e[0])
		{
		  t[0]+=INTERVAL2;//t[0]++;
          	  if (dx == dy)  
			t[1]+=INTERVAL1;//t[1]++;
	  	  else 
			t[1]-=INTERVAL1;//t[1]--;
	  	  glVertex2f(t[0],t[1]);
		}
	  }
	  glEnd();
}


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
   float a[3] = {3, 4, 1};
   float b[3] = {5, 9, 1};

   switch(opt)
   {
      case 0:
		bresenhamline(a, b);

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

