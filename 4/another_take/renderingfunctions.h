#ifndef RENDERINGFUNCTIONS_H
#define RENDERINGFUNCTIONS_H

#include <commons.h>
#include <Vertex.h>
#include <Triangle.h>

void initDraw();
int testValid(Vertex a);
void addToPointsTable(int x, int y, float z);
int clip(Vertex *a, Vertex *b);
void scanConvert(Vertex a, Vertex b);
void fillTriangle(Colour colour);
void drawTriangle(Triangle t);
void printPointsTable();
void addRectangle(Vertex a, Vertex b, Colour colour);
void initScene();
void renderScene();
void setViewer(Vertex eye, Vertex lookAt, Vertex up);
void setFrustum(float w, float h, float n, float f);

#endif // end of file

