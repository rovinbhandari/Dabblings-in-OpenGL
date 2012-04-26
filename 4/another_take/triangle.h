#ifndef TRIANGLE_INCLUDED
#define TRIANGLE_INCLUDED

#include <general.h>

typedef struct _Triangle
{
  Vertex v1, v2, v3;
  Vertex normal;
  int colour;
}Triangle;

typedef struct _TriangleList
{
  Triangle t;
  struct _TriangleList *next;
}TriangleList;

Triangle triangle(Vertex v1, Vertex v2, Vertex v3, int colour);
void freeTriangleList(TriangleList *a);
void drawTriangle(Triangle);
void drawTriangles();
void transformTriangles();
void addTransformed(Triangle a);
void addTriangle(Triangle a);
Triangle eyeTriangle(Triangle a);
Triangle globalTriangle(Triangle a);
void clearAllTriangles();

#endif // end of file
