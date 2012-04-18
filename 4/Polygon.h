/* This file contains the declaration of the Polygon class */
#ifndef POLYGON_INCLUDED
#define POLYGON_INCLUDED

#include <vector>
#include <Vector.h>

using std::vector;

class Pt2D
{
  public:
    double x, y;
    
    // Constructors
    Pt2D (double x, double y);

    // Operators
    bool operator < (const Pt2D& rhs) const;
    bool operator== (const Pt2D& rhs) const;
};

class Pt3D
{
  public:
    double x, y, z;

    // Constructors
    Pt3D (double x, double y, double z);
};

struct Color
{
  double r, g, b, i;
};

class Polygon
{
  public:
    // Constructor          
    Polygon (const vector<Pt3D>& vertices, const Vector& normal);

    // Getter functions
    Color getColor () const;
    vector<Pt3D> getVertices () const;

    // Public methods
    double xmin () const;
    double xmax () const;
    double ymin () const;
    double ymax () const;

  private:
    vector<Pt3D> vertices;
    Vector normal;
    Color rgbi;   // For color values.
    double xMax, xMin;
    double yMax, yMin;
};

#endif // End of file
