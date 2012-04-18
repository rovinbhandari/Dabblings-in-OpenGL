/* This file contains the declaration for the Vector class. */

#ifndef VECTOR_INCLUDED
#define VECTOR_INCLUDED

class Vector
{
  public:
    // Constructors
    Vector (double x, double y, double z);

    // Operations on vectors
    Vector operator+ (const Vector& rhs) const;   // Calculates the sum of two vectors
    double operator* (const Vector& rhs) const;   // Caclulates the dot product
    Vector operator- () const;                    // Unary minus
    Vector operator- (const Vector& rhs) const;   // Calculates the difference
    // Vector multiplied by a real
    Vector operator* (const double& constant) const;  // Multiplication with a real
    friend Vector operator* (const double& constant, const Vector& v);

  private:
    double x, y, z;
};

#endif    // End of file