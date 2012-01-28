#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

int o;

void initRendering(void);
void drawScene(void);
void keyboardToggler(unsigned char, int, int);

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(400, 400);
	glutCreateWindow("GG!");

	o = 0;
	//scanf("Enter choice: %d\n", &o);
	
	initRendering();

	glutKeyboardFunc(keyboardToggler);
	
	//glutReshapeFunc(resizeWindow);

	glutDisplayFunc(drawScene);

	glutMainLoop();

	//glutPostRedisplay();
	
	return 0;
}

void initRendering(void)
{
	glEnable(GL_DEPTH_TEST);

	glPointSize(8);
	glLineWidth(4);

	//fprintf(stderr, "OpenGL version: %s\n", glGetString(GL_VERSION));
}

void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

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

	glFlush();
}

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

