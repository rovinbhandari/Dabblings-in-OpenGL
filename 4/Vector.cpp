// This file contains the definition of the functions in Vector class.

#include <Vector.h>
#include <cmath>

Vector::Vector (const double x, const double y, const double z)
  : x(x), y(y), z(z)
{
}

Vector::Vector (const Pt3D& point)
  : x(point.x), y(point.y), z(point.z)
{
}

Pt3D::Pt3D (const double& x, const double& y, const double& z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

Pt3D::Pt3D (const vector<double>& pt)
{
  this->x = pt[0];
  this->y = pt[1];
  this->z = pt[2];
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

double Vector::magnitude () const
{
  return sqrt(*this * *this);
}

Vector Vector::operator/ (const double& k) const
{
  return Vector ( x / k, y / k, z / k);
}

Vector Vector::normalized () const
{
  return Vector ( *this / magnitude());
}

Vector Vector::operator % (const Vector& rhs) const
{
  return Vector (y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
}
