
#include <helper.h>

//Look at the rectangle from opposite its normal. Choose the top left and top right vertices.
void addRectangle(Vertex a, Vertex b, int colour)
{
  addTriangle(triangle(a, b, vertex(-a.x, -a.y, -a.z), colour));
  addTriangle(triangle(a, vertex(-a.x, -a.y, -a.z), vertex(-b.x, -b.y, -b.z), colour));
}

void initScene()
{
  clearAllTriangles();
}

void renderScene()
{
  initDraw();
  transformTriangles();
  drawTriangles();
}
