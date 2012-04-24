/* This file defines the class and methods of the Cuboid class. */
#include <Cuboid.h>

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
  }
}

static Vector getNormal (const int& i)
{
  return Vector (CuboidNormals[i][0], CuboidNormals[i][1], CuboidNormals[i][2]);
}

Cuboid::Cuboid (const Pt3D& point, const double& length,
                const double& breadth, const double& height)
{
  // Consider a 1 x 1 x 1 cube symmetrically with one point being 'point'. 
  vector<Pt3D> vertices (8);
  vertices[0] = Pt3D (0, 0, breadth);
	vertices[1] = Pt3D (0, 0, 0);	
	vertices[2] = Pt3D (0, height, 0);
	vertices[3] = Pt3D (0, height, breadth);
	vertices[4] = Pt3D (length, 0, breadth);
	vertices[5] = Pt3D (length, 0, 0);
	vertices[6] = Pt3D (length, height, 0);	
	vertices[7] = Pt3D (length, height, breadth);

  for ( int i = 0; i < 6; i++)
  {
    faces.push_back (Polygon (getFaceVertices (vertices, i), getNormal (i)));
  }
}
