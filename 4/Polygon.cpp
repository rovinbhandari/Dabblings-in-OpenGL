// This file contains the definition of the Polygon class
#include <Polygon.h>
#include <cfloat>
#include <iostream>
#include <cstdio>
#include <pipelineFunctions.h>
#include <sstream>

using std::stringstream;

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


/* It assumes that p1(x1,y1) & p2(x2,y2) define one line, while p3(x3,y3) and 
 * p4(x4,y4) defines another. p(x,y) is the point that needs to be checked 
 * whether it lies between the two lines.
 */
bool containedBetweenLines (const Pt3D& p, const Pt3D& p1,
                        const Pt3D& p2, const Pt3D& p3, const Pt3D& p4)
{
  double tmp1 = (p.y - p1.y) * (p1.x - p2.x)  - (p.x - p1.x) * (p1.y - p2.y);
  double tmp2 = (p.y - p3.y) * (p3.x - p4.x)  - (p.x - p3.x) * (p3.y - p4.y);

  if (tmp1 * tmp2 > 0)
  {
    std::cout << "tmp1 = " << tmp1 << ", tmp2 = " << tmp2 << "\n";
    std::cout <<   "p1.x = " << p1.x  
              << ", p1.y = " << p1.y 
              << ", p2.x = " << p2.x 
              << ", p2.y = " << p2.y 
              << ", p3.x = " << p3.x 
              << ", p3.y = " << p3.y 
              << ", p4.x = " << p4.x 
              << ", p4.y = " << p4.y 
              << ", p.x = "  <<  p.x 
              << ", p.y = "  <<  p.y 
              << "\n";
  }
  return (tmp1 * tmp2 <= 0);
}

bool Polygon::contains (const Pt3D& point) const
{
  // First check if the point lies on the plane
  if ( normal.X() * point.x + normal.Y() * point.y + normal.Z() * point.z != Deq )
  {
    return false;
  }
  
  // Check if the point is in the polygon.
  /* Check between the pairs of parallel lines only. This assumes that 
   * points occur in cyclic order only.
   */
  return (containedBetweenLines (point, vertices[0], vertices[3], 
                            vertices[1], vertices[2]) ) ?
                            containedBetweenLines (point, vertices[0],                                                    vertices[1], vertices[3],
                                             vertices[2]) : false;
}

void Polygon::applyViewTransformation (const Pt3D& eyeAt, const Vector& up,
                                       const Vector& viewNormal)
{
  int i;
  xMin = yMin = DBL_MAX;
  xMax = yMax = -DBL_MAX;
  
  for ( i = 0; i < vertices.size(); i++)
  {
    vertices[i] = world2view (vertices[i], eyeAt, up, viewNormal);
    xMax = max (xMax, vertices[i].x);
    xMin = min (xMin, vertices[i].x);

    yMax = max (yMax, vertices[i].y);
    yMin = min (yMin, vertices[i].y);
  }  

//  fprintf (stderr, "%f, %f :: %f, %f\n", xMax, xMin, yMax, yMin);
// std::cerr << xMax << "," << xMin << " :: " << yMax << "," << yMin << "\n";
  normal = Vector (world2view (Pt3D (normal), eyeAt, up, viewNormal));
}

string Polygon::toString (void) const
{
  stringstream output;
  int i;
  for (i = 0; i < vertices.size(); i++)
  {
    output << vertices[i].toString() << "\t";
  }
  output << "\n";
  return output.str();
}
