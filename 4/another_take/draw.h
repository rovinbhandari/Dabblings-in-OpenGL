#ifndef DRAW_INCLUDED
#define DRAW_INCLUDED

#include <general.h>
#include <triangle.h>

void initDraw();
int testValid(Vertex a);
void addToPointsTable(int x, int y, float z);
int clip(Vertex *a, Vertex *b);
void scanConvert(Vertex a, Vertex b);
void fillTriangle(int colour);
void drawTriangle(Triangle t);
void printPointsTable();

#endif // end of file
