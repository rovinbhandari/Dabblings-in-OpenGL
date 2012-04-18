// This file contains the definition of the functions in Vector class.

#include <Vector.h>

Vector::Vector (double x, double y, double z)
  : x(x), y(y), z(z)
{
}

Vector Vector::operator+ (const Vector& rhs) const
{
  return Vector(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vector Vector::operator- () const
{
  return Vector(-x, -y, -z);
}

double Vector::operator* (const Vector& rhs) const
{
  return (x * rhs.x + y * rhs.y + z * rhs.z);
}

Vector Vector::operator- (const Vector& rhs) const
{
  // return (this + (-rhs));    // doesn't work :-/
  return (this->operator+(-rhs));
}

Vector Vector::operator* (const double& k) const
{
  return Vector(k * x, k * y, k * z);
}

Vector operator* (const double& k, const Vector& v)
{
  return (v * k);
}
