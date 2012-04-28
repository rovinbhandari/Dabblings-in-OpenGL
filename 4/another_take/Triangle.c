#include <Triangle.h>
#include <matrixmanipulation.h>

Triangle triangle(Vertex v1, Vertex v2, Vertex v3, Colour colour)
{
  Triangle a;
  a.v1=v1; a.v2=v2; a.v3=v3; a.colour=colour;
  return a;
}

TriangleList *globalTriangles=NULL;
TriangleList *transformedTriangles=NULL;

void freeTriangleList(TriangleList *a)
{
  if(!a)	return;
  freeTriangleList(a->next);
  free(a);
}

void clearAllTriangles()
{
  freeTriangleList(globalTriangles);
  globalTriangles=NULL;
  freeTriangleList(transformedTriangles);
  transformedTriangles=NULL;
}

Triangle globalTriangle(Triangle a)
{
  float light;
  Triangle t_a = triangle(globalVertex(a.v1), globalVertex(a.v2), globalVertex(a.v3), a.colour);
  t_a.normal = crossProduct(subVertex(t_a.v2, t_a.v1), subVertex(t_a.v3, t_a.v2));
  t_a.normal = normalizeVertex(t_a.normal);
  light=dotProduct(normalizeVertex(t_a.v1), normalizeVertex(vertex(0, 0, 5)));
  t_a.colour=(a.colour*(int)((light*0.5)*127))/127 + (a.colour*63)/127;
  return t_a;
}

Triangle eyeTriangle(Triangle a)
{
  Triangle t_a = triangle(eyeVertex(a.v1), eyeVertex(a.v2), eyeVertex(a.v3), a.colour);
  t_a.normal = crossProduct(subVertex(t_a.v2, t_a.v1), subVertex(t_a.v3, t_a.v2));
  t_a.normal = normalizeVertex(t_a.normal);
  return t_a;
}

void addTriangle(Triangle a)
{
  Triangle t_a = globalTriangle(a);
  TriangleList *temp=(TriangleList *)malloc(sizeof(TriangleList)), *curr;
  temp->t=t_a;
  temp->next=NULL;
  if(!globalTriangles)	globalTriangles=temp;
  else{
    curr=globalTriangles;
    while(curr->next){
      curr=curr->next;
    }
    curr->next=temp;
  }
}

void addTransformed(Triangle a)
{
  TriangleList *temp=(TriangleList *)malloc(sizeof(TriangleList)), *curr;
  temp->t=a;
  temp->next=NULL;
  if(!transformedTriangles)	transformedTriangles=temp;
  else{
    curr=transformedTriangles;
    while(curr->next){
      curr=curr->next;
    }
    curr->next=temp;
  }
}

void transformTriangles()
{
  TriangleList *currTriangle;
  Triangle t;
  for(currTriangle=globalTriangles; currTriangle; currTriangle=currTriangle->next){
    t=eyeTriangle(currTriangle->t);
    if(t.normal.z<=0)	continue;
    addTransformed(t);
  }
}

void drawTriangles()
{
 TriangleList *currTriangle;
 for(currTriangle=transformedTriangles; currTriangle; currTriangle=currTriangle->next)
 {
   drawTriangle(currTriangle->t);
 }
}

