#include <Polygon.h>
#include <iostream>
#include <pipelineFunctions.h>
#include <list>

using std::list;


int main (void)
{
	vector<Pt3D> vertices;
  Color c;
  c.r = c.g = c.b = 1;
	
	vertices.push_back(Pt3D());
	vertices.push_back(Pt3D(1,0,0));
	vertices.push_back(Pt3D(1,1,0));
	vertices.push_back(Pt3D(0,1,0));

	Polygon t (vertices, Vector (0,0,1));
  t.setColor (c);
	std::cerr << "Polygon 1 ready\n";

  c.r = c.g = c.b = 0;
	vertices.clear();
	vertices.push_back(Pt3D(0,0,-1));
	vertices.push_back(Pt3D(1,0,-1));
	vertices.push_back(Pt3D(1,1,-1));
	vertices.push_back(Pt3D(0,1,-1));

	Polygon u (vertices, Vector(0,0,1));
  u.setColor (c);
	std::cerr << "Polygon 2 ready\n";

	list<Polygon> l;
	l.push_back(u);
	l.push_back(t);

	map<Pt2D,Color> depth = depthBufferMethod (l);
  map<Pt2D,Color>::iterator itr;
  for (itr = depth.begin(); itr != depth.end(); itr++)
  {
    std::cerr << itr->first.x  << "," << itr->first.y << "  -- "
              << itr->second.r << ","
              << itr->second.g << ","
              << itr->second.b << "\n";
  }
  std::cerr << "Buffer\n";

	return 0;
}
