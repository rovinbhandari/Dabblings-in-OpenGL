/* This file defines the class and methods of the Cuboid class. */
#include <Cuboid.h>
#include <iostream>

static double CuboidNormals[6][3] = {
			{-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
			{0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0}
				    };
static int CuboidFaces[6][4] = {
			{0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
			{4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3}
			       };

static vector<Pt3D> getFaceVertices (const vector <Pt3D>& vertices, const int& i)
{
  vector <Pt3D> ret(4);
  for (int j = 0; j < 4; j++)
  {
    ret[j] = vertices[CuboidFaces[i][j]];
    std::cerr << ret[j].toString() << "\n";
  }
  return ret;
}

static Vector getNormal (const int& i)
{
  return Vector (CuboidNormals[i][0], CuboidNormals[i][1], CuboidNormals[i][2]);
}

Cuboid::Cuboid (const Pt3D& point, const double& length,
                const double& breadth, const double& height)
{
  std::cerr << "In Cuboid()\n";
  // Consider a 1 x 1 x 1 cube symmetrically with one point being 'point'. 
  vector<Pt3D> vertices (8);
  double x = point.x, y = point.y, z = point.z;
  std::cerr << x << "," << y << "," << z << "\n";
  vertices[0] = Pt3D (x, y, z + breadth);
	vertices[1] = Pt3D (x, y, z);	
	vertices[2] = Pt3D (x, y + height, z);
	vertices[3] = Pt3D (x, y + height, z + breadth);
	vertices[4] = Pt3D (x + length, y, z + breadth);
	vertices[5] = Pt3D (x + length, y, z);
	vertices[6] = Pt3D (x + length, y + height, z);	
	vertices[7] = Pt3D (x + length, y + height, z + breadth);

  for ( int i = 0; i < 6; i++)
  {
    std::cerr << "iterating for i = " << i << "\n";
    faces.push_back (Polygon (getFaceVertices (vertices, i), getNormal (i)));
    faces[i].setColor (Color (1,1,1));
  }
}

list<Polygon> Cuboid::toPolygonList (void)
{
  int i; 
  list<Polygon> retList;
  std::cerr << "Creating List\n";
  for (i = 0; i < faces.size(); i++)
  {
    retList.push_back (faces[i]);
  }
  
  std::cerr << "Returning List\n";
  return retList;
}
