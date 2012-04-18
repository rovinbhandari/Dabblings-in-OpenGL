/* This file contains the declaration of the Polygon class */
#ifndef POLYGON_INCLUDED
#define POLYGON_INCLUDED

#include <vector>
#include <Vector.h>

using std::vector;

/*
struct Pt2D
{
  double x, y, z;
};
*/
struct Pt3D
{
    double x, y, z;
};

class Polygon
{
  public:
    // Constructor          

  private:
    vector<Pt3D> vertices;
    Vector Normal;
    double rgbi[4];   // For color values.
};

#endif // End of file
