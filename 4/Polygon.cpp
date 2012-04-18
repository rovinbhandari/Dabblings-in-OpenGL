// This file contains the definition of the Polygon class
#include <Polygon.h>

Polygon::Polygon (const vector<Pt3D>& vertices, const Vector& normal)
  : vertices (vertices), normal (normal) 
{
}

Pt2D::Pt2D (double x, double y)
  : x(x), y(y)
{
}

bool Pt2D::operator < (const Pt2D& rhs) const
{
  return (x < rhs.x) ? (y < rhs.y) : (false);
}

bool Pt2D::operator == (const Pt2D& rhs) const
{
  return (x == rhs.x) ? (y == rhs.y) : false;
}

double Polygon::xmin () const
{
}

double Polygon::ymin () const
{
}

double Polygon::xmax () const
{
}

double Polygon::ymax () const
{
}
