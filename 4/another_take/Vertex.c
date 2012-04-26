#include <Vertex.h>
#include <math.h>

Vertex vertex(float x, float y, float z)
{
  Vertex a;
  a.x = x;
  a.y = y;
  a.z = z;
  return a;
}

Vertex subVertex(Vertex a, Vertex b)
{
  return vertex(a.x-b.x, a.y-b.y, a.z-b.z);
}

float dotProduct(Vertex a, Vertex b)
{
  return a.x*b.x+a.y*b.y+a.z*b.z;
}

Vertex crossProduct(Vertex a, Vertex b)
{
  Vertex c;
  c.x=a.y*b.z-a.z*b.y;
  c.y=a.z*b.x-a.x*b.z;
  c.z=a.x*b.y-a.y*b.x;
  return c;
}

float modVertex(Vertex a)
{
  return sqrt(pow(a.x,2)+pow(a.y,2)+pow(a.z,2));
}

Vertex normalizeVertex(Vertex a)
{
  float mod=modVertex(a);
  return vertex(a.x/mod, a.y/mod, a.z/mod);
}

