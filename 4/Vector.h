/* This file contains the declaration for the Vector class. */

#ifndef VECTOR_INCLUDED
#define VECTOR_INCLUDED

#include <vector>
using std::vector;

class Pt2D
{
  public:
    double x, y;
    
    // Constructors
    Pt2D (const double& x = 0, const double& y = 0);

    // Operators
    bool operator < (const Pt2D& rhs) const;
    bool operator== (const Pt2D& rhs) const;
};

class Pt3D
{
  public:
    double x, y, z;

    // Constructors
    Pt3D (const double& x = 0, const double& y = 0, const double& z = 0);
    Pt3D (const vector<double>& pt); // Assumes at least three entries
};

class Vector
{
  public:
    // Constructors
    Vector (const double x = 0, const double y = 0, const double z = 0);
    Vector (const Pt3D& point);

    // Operations on vectors
    Vector operator+ (const Vector& rhs) const;   // Calculates the sum of two vectors
    double operator* (const Vector& rhs) const;   // Caclulates the dot product
    Vector operator- () const;                    // Unary minus
    Vector operator- (const Vector& rhs) const;   // Calculates the difference
    // Vector multiplied by a real
    Vector operator* (const double& constant) const;  // Multiplication with a real
    friend Vector operator* (const double& constant, const Vector& v);
    double magnitude () const;

    // Getters
    double X() const { return x; }
    double Y() const { return y; }
    double Z() const { return z; }


  private:
    double x, y, z;
};

#endif    // End of file
