#ifndef VERTEX_H
#define VERTEX_H

typedef struct _Vertex
{
  float x, y, z;
} Vertex;

Vertex vertex(float x, float y, float z);
Vertex subVertex(Vertex a, Vertex b);
float dotProduct(Vertex a, Vertex b);
Vertex crossProduct(Vertex a, Vertex b);
float modVertex(Vertex a);
Vertex normalizeVertex(Vertex a);

#endif // end of file

