/* This file contains the declaration of the Polygon class */
#ifndef POLYGON_INCLUDED
#define POLYGON_INCLUDED

#include <vector>
#include <Vector.h>

using std::vector;


struct Color
{
  double r, g, b, i;
  
  Color (const double& r = 0, const double& g = 0, const double& b = 0)
  { this->r = r; this->g = g; this->b = b; }
};

class Polygon
{
  public:
    // Constructor          
    Polygon (const vector<Pt3D>& vertices, const Vector& normal);

    // Getter functions
    Color getColor () const;
    vector<Pt3D> getVertices () const;
    double A() const { return normal.X(); }
    double B() const { return normal.Y(); }
    double C() const { return normal.Z(); }
    double D() const { return Deq; }

    // Set color 
    void setColor (const Color& color);

    // Public methods
    double xmin () const;
    double xmax () const;
    double ymin () const;
    double ymax () const;
    bool contains (const Pt3D& point) const;
    string toString () const;    
    void applyViewTransformation (const Pt3D& eyeAt, const Vector& up, 
                                  const Vector& viewNormal);
  private:
    vector<Pt3D> vertices;
    double Deq;
    Vector normal;
    Color rgbi;   // For color values.
    double xMax, xMin;
    double yMax, yMin;
};

#endif // End of file
