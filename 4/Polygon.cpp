// This file contains the definition of the Polygon class
#include <Polygon.h>
#include <cfloat>

inline double min (const double& a, const double& b)
{
  return (a < b) ? a : b;
}

inline double max (const double& a, const double& b)
{
  return (a > b) ? a : b;
}

Polygon::Polygon (const vector<Pt3D>& vertices, const Vector& normal)
  : vertices (vertices), normal (normal) 
{
  // Calculate xmin, ymin, xmax and ymax and store it.
  int i;
  xMin = yMin = DBL_MAX;
  xMax = yMax = -DBL_MAX;
  for ( i = 0; i < vertices.size(); i++)
  {
    xMax = max (xMax, vertices[i].x);
    xMin = min (xMin, vertices[i].x);

    yMax = max (yMax, vertices[i].y);
    yMin = min (yMin, vertices[i].y);
  }

  // Store the value of 'D', which is the distance along the normal vector to the 
  // origin.
  Deq = Vector(vertices[0]) * normal;
}

Pt2D::Pt2D (const double& x, const double& y)
{
  this->x = x;
  this->y = y;
}

/* IMPORTANT : This function plays an important role in the map.
 * When this didn't work correctly, the map showed only points of the form
 * (x,x).
 */
bool Pt2D::operator < (const Pt2D& rhs) const
{
  return (x < rhs.x) ? true : (x == rhs.x) ? (y < rhs.y) : false;
}

bool Pt2D::operator == (const Pt2D& rhs) const
{
  return (x == rhs.x) ? (y == rhs.y) : false;
}

double Polygon::xmin () const
{
  return xMin;
}

double Polygon::ymin () const
{
  return yMin;
}

double Polygon::xmax () const
{
  return xMax;
}

double Polygon::ymax () const
{
  return yMax;
}

Pt3D::Pt3D (const double& x, const double& y, const double& z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

Color Polygon::getColor () const
{
  return this->rgbi;
}

vector<Pt3D> Polygon::getVertices () const
{
  return vertices;
}


void Polygon::setColor (const Color& color)
{
  rgbi = color;
}
