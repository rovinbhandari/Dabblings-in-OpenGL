#include "3Dobjects.h"

int o;
GLfloat viewangle;

void initRendering(void);
void drawScene(void);	//TODO: add options for AND, OR, 1 MINUS 2, 2 MINUS 1, SHOW 1, SHOW 2.
void keyboardToggler(unsigned char, int, int);	//TODO: add movement using wasd and rotation using qe.

int main(int argc, char* argv[])
{
	static GLfloat lightpos[] = {25.0f, 50.0f, -50.0f, 1.0f};
	static GLfloat specs_sphere[] = {1.0f, 0.5f, 0.0f, 1.0f};
	static GLfloat specs_cone[] = {1.0f, 0.5f, 1.0f, 1.0f};
	GLUquadricObj *sphere, *cone, *base;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_STENCIL | GLUT_DEPTH | GLUT_DOUBLE);
	//glutInitWindowPosition(300, 300);
	glutInitWindowSize(400, 400);
	glutCreateWindow("GG!");

	initRendering();
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glutKeyboardFunc(keyboardToggler);
	
	glutDisplayFunc(drawScene);
	
	glNewList(SPHERE, GL_COMPILE);
	sphere = gluNewQuadric();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, specs_sphere);
	gluSphere(sphere, 20.0f, 64, 64);
	gluDeleteQuadric(sphere);
	glEndList();

	glNewList(CONE, GL_COMPILE);
	cone = gluNewQuadric();
	base = gluNewQuadric();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, specs_cone);
	gluQuadricOrientation(base, GLU_INSIDE);
	gluDisk(base, 0.0, 15.0, 64.0, 1);
	gluCylinder(cone, 15.0, 0.0, 60.0, 64, 64);
	gluDeleteQuadric(cone);
	gluDeleteQuadric(base);
	glEndList();

	glMatrixMode(GL_PROJECTION);
	glOrtho(-50.0, 50.0, -50.0, 50.0, -50.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
	
	glutMainLoop();

	return 0;
}


void initRendering(void)
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

//TODO
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glRotatef(viewangle, 0.0f, 1.0f, 0.0f);

	switch(o)
	{
		case 0:
			glColor3f(1.0, 1.0, 1.0);

			break;
		
		case 1:
			glBegin(GL_POINTS);
			
			glVertex2f(0.0, 0.0);
			glVertex2f(0.0, 0.5);
			glVertex2f(0.5, 0.0);
			glVertex2f(-0.5, 0.0);
			glVertex2f(0.0, -0.5);
			glVertex2f(0.5, 0.5);
			glVertex2f(-0.5, 0.5);
			glVertex2f(0.5, -0.5);

			glEnd();

			break;

		case 2:
			glBegin(GL_LINES);

			glVertex2f(0.0, 0.0);
			glVertex2f(0.5, 0.5);
			
			glVertex2f(0.5, -1.0);
			glVertex2f(0.3, 0.0);
			
			glEnd();

			break;

		case 3:
			glBegin(GL_TRIANGLES);
			glColor3f(1.0, 0.0, 0.0);
			glVertex2f(0.3, 1.0);
			glVertex2f(0.7, 0.1);
			glVertex2f(0.9, 1.0);

			glEnd();

			break;

		default:
			fprintf(stderr, "LOL!\n");
	}

	glPopMatrix();
	glutSwapBuffers();

	glFlush();
}

//TODO
void keyboardToggler(unsigned char c, int x, int y)
{
	switch(c)
	{
		case 27:
			exit(1);

			break;

		default:
			o = (int) (c - '0');
			//fprintf(stderr, "\to = %d\n", o);
			glutPostRedisplay();

			break;
	}
}

