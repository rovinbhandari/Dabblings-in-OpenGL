#include <stdbool.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <time.h>
#include <commons.h>
#include <Vertex.h>
#include <matrixmanipulation.h>
#include <Triangle.h>
#include <renderingfunctions.h>

float _anglex, _angley, _eyex=0.0, _eyez=2.0;
int MAX_H, MAX_W;
int WxH;
int posB=0;
GLint rasterPos[4];
float eyex=0, eyey=0, eyez=16, lookx=0, looky=0, lookz=0, upx=0, upy=1, upz=0;
float Bx = 2, By = 0, Bz = 0;
float Ax = -5, Ay = -3, Az = 0;
unsigned int *data;
Boolean Aisclippingwindow = FALSE;

void blockWithHole(float x, float y, float z){
  addToStack();
    translate(x, y, z);
    addToStack();
      translate(2.5, 0.0, 0.0);
      addRectangle(vertex(0.0, 1.5, 2.5), vertex(0.0, -1.5, 2.5), YELLOW);
      translate(-5.0, 0.0, 0.0);
      addRectangle(vertex(0.0, -1.5, 2.5), vertex(0.0, 1.5, 2.5), YELLOW);
    removeFromStack();
    addToStack();
      translate(0.5, 0.0, 0.0);
      addRectangle(vertex(0.0, -1.5, 0.5), vertex(0.0, 1.5, 0.5), GREY);
      translate(-1.0, 0.0, 0.0);
      addRectangle(vertex(0.0, 1.5, 0.5), vertex(0.0, -1.5, 0.5), GREY);
    removeFromStack();
    addToStack();
      translate(0.0, 0.0, 2.5);
      addRectangle(vertex(-2.5, 1.5, 0.0), vertex(-2.5, -1.5, 0.0), YELLOW);
      translate(0.0, 0.0, -5.0);
      addRectangle(vertex(-2.5, -1.5, 0.0), vertex(-2.5, 1.5, 0.0), YELLOW);
    removeFromStack();
    addToStack();
      translate(0.0, 0.0, 0.5);
      addRectangle(vertex(-0.5, -1.5, 0.0), vertex(-0.5, 1.5, 0.0), GREY);
      translate(0.0, 0.0, -1.0);
      addRectangle(vertex(-0.5, 1.5, 0.0), vertex(-0.5, -1.5, 0.0), GREY);
    removeFromStack();
    addToStack();
      translate(1.5, 1.5, 0.0);
      addRectangle(vertex(-1.0, 0.0, -0.5), vertex(-1.0, 0.0, 0.5), YELLOW);
      addToStack();
        translate(0.0, -3.0, 0.0);
        addRectangle(vertex(-1.0, 0.0, 0.5), vertex(-1.0, 0.0, -0.5), YELLOW);
      removeFromStack();
      translate(-3.0, 0.0, 0.0);
      addRectangle(vertex(-1.0, 0.0, -0.5), vertex(-1.0, 0.0, 0.5), YELLOW);
      addToStack();
        translate(0.0, -3.0, 0.0);
        addRectangle(vertex(-1.0, 0.0, 0.5), vertex(-1.0, 0.0, -0.5), YELLOW);
      removeFromStack();
    removeFromStack();
    addToStack();
      translate(0.0, 1.5, 1.5);
      addRectangle(vertex(-2.5, 0.0, -1.0), vertex(-2.5, 0.0, 1.0), YELLOW);
      addToStack();
        translate(0.0, -3.0, 0.0);
        addRectangle(vertex(-2.5, 0.0, 1.0), vertex(-2.5, 0.0, -1.0), YELLOW);
      removeFromStack();
      translate(0.0, 0.0, -3.0);
      addRectangle(vertex(-2.5, 0.0, -1.0), vertex(-2.5, 0.0, 1.0), YELLOW);
      addToStack();
        translate(0.0, -3.0, 0.0);
        addRectangle(vertex(-2.5, 0.0, 1.0), vertex(-2.5, 0.0, -1.0), YELLOW);
      removeFromStack();
    removeFromStack();
  removeFromStack();
} 

#define Bpart(X)	do	\
			{	\
				addToStack();	\
					addRectangle(vertex(0.0, 1.5, -0.5), vertex(0.0, -1.5, -0.5), X);	\
					translate(1.0, 0.0, 0.0);	\
					addRectangle(vertex(0.0, -1.5, -0.5), vertex(0.0, 1.5, -0.5), X);	\
					translate(-0.5, 0.0, -0.5);	\
					addRectangle(vertex(0.5, 1.5, 0.0), vertex(0.5, -1.5, 0.0), X);		\
					translate(0.0, 0.0, 1.0);	\
					addRectangle(vertex(0.5, -1.5, 0.0), vertex(0.5, 1.5, 0.0), X);		\
				removeFromStack();	\
			}	\
			while(0)
#define Bredcap		do	\
			{	\
				addRectangle(vertex(-0.5, 0.0, 0.5), vertex(-0.5, 0.0, -0.5), RED);	\
			}	\
			while(0)
#define Bgreencap	do	\
			{	\
				addRectangle(vertex(-0.5, 0.0, -0.5), vertex(-0.5, 0.0, 0.5), GREEN);	\
			}	\
			while(0)
void drawB(float x, float y, float z){
  if(Aisclippingwindow && (posB == 0 || posB == 1))
  	return;
  addToStack();
    translate(x, y, z);
    if(Aisclippingwindow)
    {
	if(posB == 2)
	{
		translate(-0.5, -3.0, 0.0);
		Bpart(RED);
	}
	else if(posB == 3)
	{
		translate(-0.5, 0.0, 0.0);
		Bpart(BLUE);
	}
    	else if(posB == 4)
	{
		translate(-0.5, 3.0, 0.0);
		Bpart(GREEN);
	}
    }
    else
    {
	translate(-0.5, -3.0, 0.0);
	Bpart(RED);
	translate(0.0, 3.0, 0.0);
	Bpart(BLUE);
	translate(0.0, 3.0, 0.0);
    	Bpart(GREEN);
	translate(0.5, 1.5, 0.0);
	Bgreencap;
	translate(0.0, -9.0, 0.0);
	Bredcap;
    }
  removeFromStack();
}

void onDraw()
{
  /*setViewer O(1)*/
  setMatrixMode(PROJECTION);
  initMatrix();
  setViewer(vertex(eyex, eyey, eyez), vertex(lookx, looky, lookz), vertex(upx, upy, upz));
  setFrustum(10, 10*MAX_H/MAX_W, 4, 25);

  /*createPolygons O(1)*/
  initScene();
  setMatrixMode(MODELVIEW); 
  initMatrix();
  if(!Aisclippingwindow)
	blockWithHole(Ax, Ay, Az);
  drawB(Bx, By, Bz);

 
  /*calcData*/
  /*
    For each polygon,
      Go to next triangle if current polygon doesn't face viewer O(1)
      Calculate pixel values of vertices of the triangle O(1)
      clip triangle  //unless you model your scene such that no part ever goes outside the viewport (commentception) O(1)
      For each triangle, O(m*n)
        Add x,y,z position of scan conversion pixels to temp per-polygon table (indexed on y position with min and max x values)
        Also store a min and max x for y=0, y=MAX_Y-1. Add the x,y values for the points in between to the temp table
        Copy temp table to data table with the points between min and max x values filled (in case of conlict, min z value only) O(m*n)
  */

  /*drawPixels*/
  renderScene();
  glDrawPixels(MAX_W, MAX_H, GL_RGBA, GL_BYTE, data);
  glFlush();
}

void moveB(int k){
  switch(k){
    case 0:
      Bx = -5;
      By = 6 + Ay;
      onDraw();
      break;
    case 1:
      By = 3 + Ay;
      onDraw();
      break;
    case 2:
      By = 0 + Ay;
      onDraw();
      break;
    case 3:
      By = -3 + Ay;
      onDraw();
      break;
    default:
      posB = 0;
      Bx = 2;
      By = 0;
      onDraw();
      break;
  }
}

void keyPressed(unsigned char x, int i, int j)
{
  switch(x){
    case 'x': exit(0);
    case 'z': Aisclippingwindow = !Aisclippingwindow;
              break;
    case 'a': eyex-=0.5;
              break;
    case 'd': eyex+=0.5;
              break;
    case 'w': eyez-=0.5;
              break;
    case 's': eyez+=0.5;
              break;
    case 'q': eyey+=0.5;
              break;
    case 'e': eyey-=0.5;
              break;
    case 'n': moveB(posB++);
              break;
  }
  onDraw();
}


int main(int argc, char** argv)
{
  if(argc > 2)
  {
  	MAX_W=atoi(argv[1]);
  	MAX_H=atoi(argv[2]);
  }
  else
  {
  	MAX_W = 1200;
	MAX_H = 750;
  }
  WxH=MAX_W*MAX_H;
  data = (unsigned int *)malloc(WxH*sizeof(unsigned int));
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH );
  glutInitWindowSize(MAX_W,MAX_H);
  glutInitWindowPosition(0,0);
  glutCreateWindow("HSR");
  glutDisplayFunc(onDraw);
  glutKeyboardFunc(keyPressed);
  glutMainLoop();    
  return 0;
}

