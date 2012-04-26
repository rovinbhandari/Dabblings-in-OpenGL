#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>
#include<GL/freeglut.h>
#include<math.h>
#include<time.h>
#include "general.h"
#include "matrix.h"
#include "triangle.h"
#include "draw.h"
#include "helper.h"
#include "view.h"

float _anglex, _angley, _eyex=0.0, _eyez=2.0;
int MAX_H, MAX_W;
int WxH;
int posB=0;
GLint rasterPos[4];
float eyex=0, eyey=0, eyez=10, lookx=0, looky=0, lookz=0, upx=0, upy=1, upz=0;
float barx=2, bary=0;
unsigned int *data;

void blockWithHole(float x, float y, float z){
  int yellow=127+(127<<8), grey=100+(100<<8)+(100<<16);
  pushMatrix();
    translate(x, y, z);
    pushMatrix();
      translate(2.5, 0.0, 0.0);
      addRectangle(vertex(0.0, 1.5, 2.5), vertex(0.0, -1.5, 2.5), yellow);
      translate(-5.0, 0.0, 0.0);
      addRectangle(vertex(0.0, -1.5, 2.5), vertex(0.0, 1.5, 2.5), yellow);
    popMatrix();
    pushMatrix();
      translate(0.5, 0.0, 0.0);
      addRectangle(vertex(0.0, -1.5, 0.5), vertex(0.0, 1.5, 0.5), grey);
      translate(-1.0, 0.0, 0.0);
      addRectangle(vertex(0.0, 1.5, 0.5), vertex(0.0, -1.5, 0.5), grey);
    popMatrix();
    pushMatrix();
      translate(0.0, 0.0, 2.5);
      addRectangle(vertex(-2.5, 1.5, 0.0), vertex(-2.5, -1.5, 0.0), yellow);
      translate(0.0, 0.0, -5.0);
      addRectangle(vertex(-2.5, -1.5, 0.0), vertex(-2.5, 1.5, 0.0), yellow);
    popMatrix();
    pushMatrix();
      translate(0.0, 0.0, 0.5);
      addRectangle(vertex(-0.5, -1.5, 0.0), vertex(-0.5, 1.5, 0.0), grey);
      translate(0.0, 0.0, -1.0);
      addRectangle(vertex(-0.5, 1.5, 0.0), vertex(-0.5, -1.5, 0.0), grey);
    popMatrix();
    pushMatrix();
      translate(1.5, 1.5, 0.0);
      addRectangle(vertex(-1.0, 0.0, -0.5), vertex(-1.0, 0.0, 0.5), yellow);
      pushMatrix();
        translate(0.0, -3.0, 0.0);
        addRectangle(vertex(-1.0, 0.0, 0.5), vertex(-1.0, 0.0, -0.5), yellow);
      popMatrix();
      translate(-3.0, 0.0, 0.0);
      addRectangle(vertex(-1.0, 0.0, -0.5), vertex(-1.0, 0.0, 0.5), yellow);
      pushMatrix();
        translate(0.0, -3.0, 0.0);
        addRectangle(vertex(-1.0, 0.0, 0.5), vertex(-1.0, 0.0, -0.5), yellow);
      popMatrix();
    popMatrix();
    pushMatrix();
      translate(0.0, 1.5, 1.5);
      addRectangle(vertex(-2.5, 0.0, -1.0), vertex(-2.5, 0.0, 1.0), yellow);
      pushMatrix();
        translate(0.0, -3.0, 0.0);
        addRectangle(vertex(-2.5, 0.0, 1.0), vertex(-2.5, 0.0, -1.0), yellow);
      popMatrix();
      translate(0.0, 0.0, -3.0);
      addRectangle(vertex(-2.5, 0.0, -1.0), vertex(-2.5, 0.0, 1.0), yellow);
      pushMatrix();
        translate(0.0, -3.0, 0.0);
        addRectangle(vertex(-2.5, 0.0, 1.0), vertex(-2.5, 0.0, -1.0), yellow);
      popMatrix();
    popMatrix();
  popMatrix();
} 

void blockColoured(float x, float y, float z){
  pushMatrix();
    translate(x, y, z);
    translate(-0.5, -3.0, 0.0);
    pushMatrix();
       addRectangle(vertex(0.0, 1.5, -0.5), vertex(0.0, -1.5, -0.5), 127<<8);
       translate(1.0, 0.0, 0.0);
       addRectangle(vertex(0.0, -1.5, -0.5), vertex(0.0, 1.5, -0.5), 127<<8);
       translate(-0.5, 0.0, -0.5);
       addRectangle(vertex(0.5, 1.5, 0.0), vertex(0.5, -1.5, 0.0), 127<<8);
       translate(0.0, 0.0, 1.0);
       addRectangle(vertex(0.5, -1.5, 0.0), vertex(0.5, 1.5, 0.0), 127<<8);
    popMatrix();
    translate(0.0, 3.0, 0.0);
    pushMatrix();
       addRectangle(vertex(0.0, 1.5, -0.5), vertex(0.0, -1.5, -0.5), 127<<16);
       translate(1.0, 0.0, 0.0);
       addRectangle(vertex(0.0, -1.5, -0.5), vertex(0.0, 1.5, -0.5), 127<<16);
       translate(-0.5, 0.0, -0.5);
       addRectangle(vertex(0.5, 1.5, 0.0), vertex(0.5, -1.5, 0.0), 127<<16);
       translate(0.0, 0.0, 1.0);
       addRectangle(vertex(0.5, -1.5, 0.0), vertex(0.5, 1.5, 0.0), 127<<16);
    popMatrix();
    translate(0.0, 3.0, 0.0);
    pushMatrix();
       addRectangle(vertex(0.0, 1.5, -0.5), vertex(0.0, -1.5, -0.5), 127);
       translate(1.0, 0.0, 0.0);
       addRectangle(vertex(0.0, -1.5, -0.5), vertex(0.0, 1.5, -0.5), 127);
       translate(-0.5, 0.0, -0.5);
       addRectangle(vertex(0.5, 1.5, 0.0), vertex(0.5, -1.5, 0.0), 127);
       translate(0.0, 0.0, 1.0);
       addRectangle(vertex(0.5, -1.5, 0.0), vertex(0.5, 1.5, 0.0), 127);
    popMatrix();
    translate(0.5, 1.5, 0.0);
    addRectangle(vertex(-0.5, 0.0, -0.5), vertex(-0.5, 0.0, 0.5), 127);
    translate(0.0, -9.0, 0.0);
    addRectangle(vertex(-0.5, 0.0, 0.5), vertex(-0.5, 0.0, -0.5), 127<<8);
  popMatrix();
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
  blockWithHole(-5.0,0.0,0.0);
  blockColoured(barx, bary, 0.0);

 
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
      barx = -5;
      bary = 6;
      onDraw();
      break;
    case 1:
      bary = 3;
      onDraw();
      break;
    case 2:
      bary = 0;
      onDraw();
      break;
    case 3:
      bary = -3;
      onDraw();
      break;
    default:
      posB = 0;
      barx = 2;
      bary = 0;
      onDraw();
      break;
  }
}

void keyPressed(unsigned char x, int i, int j)
{
  switch(x){
    case 'x': exit(0);
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
    case ' ': moveB(posB++);
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
  	MAX_W = 800;
	MAX_H = 600;
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

