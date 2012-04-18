#include <Polygon.h>
#include <iostream>
#include <pipelineFunctions.h>
#include <list>

using std::list;


int main (void)
{
	vector<Pt3D> vertices;
	
	vertices.push_back(Pt3D());
	vertices.push_back(Pt3D(1,0,0));
	vertices.push_back(Pt3D(1,1,0));
	vertices.push_back(Pt3D(0,1,0));

	Polygon t (vertices, Vector (0,0,1));
	std::cerr << "Polygon 1 ready\n";
	vertices.clear();
	vertices.push_back(Pt3D(0,0,1));
	vertices.push_back(Pt3D(1,0,1));
	vertices.push_back(Pt3D(1,1,1));
	vertices.push_back(Pt3D(0,1,1));

	Polygon u (vertices, Vector(0,0,1));
	std::cerr << "Polygon 2 ready\n";

	list<Polygon> l;
	l.push_back(t);
	l.push_back(u);

	depthBufferMethod (l)[Pt2D(0.1, 0.1)];
	std::cerr << "Buffer\n";

	return 0;
}
