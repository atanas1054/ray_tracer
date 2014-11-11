#include <core/vector.h>
#include <core/point.h>
#include <cmath>

namespace rt{

Vector Vector::operator+(const Vector& b) const {
	return Vector(x + b.x, y + b.y, z + b.z);
}
Vector Vector::operator-(const Vector& b) const {
	return Vector(x - b.x, y - b.y, z - b.z);
}
Vector Vector::normalize() const {
	return Vector(x, y, z) / length();
}  
Vector Vector::operator-() const {
	return Vector(-x, -y, -z);
}
float Vector::lensqr() const {
	return x*x + y*y + z*z;
}
float Vector::length() const {
	return std::sqrtf(lensqr());
}
bool Vector::operator==(const Vector& b) const{
	return x == b.x && y == b.y && z == b.z;
}
bool Vector::operator!=(const Vector& b) const {
	return x != b.x && y != b.y && z != b.z;
}

Vector operator*(float scalar, const Vector& b) {
	return Vector(scalar * b.x, scalar * b.y, scalar * b.z);
}
Vector operator*(const Vector& a, float scalar) {
	return Vector(scalar * a.x, scalar * a.y, scalar * a.z);
}
Vector operator/(const Vector& a, float scalar) {
	return Vector(a.x / scalar, a.y / scalar, a.z / scalar);
}
Vector cross(const Vector& a, const Vector& b) {
	return Vector(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}
float dot(const Vector& a, const Vector& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector min(const Vector& a, const Vector& b) {
	return Vector(
		a.x < b.x ? a.x : b.x,
		a.y < b.y ? a.y : b.y,
		a.z < b.z ? a.z : b.z
	);
}
Vector max(const Vector& a, const Vector& b) {
	return Vector(
		a.x > b.x ? a.x : b.x,
		a.y > b.y ? a.y : b.y,
		a.z > b.z ? a.z : b.z
	);
}

Point operator+(const Point& a, const Vector& b) {
	return Point(
		a.x + b.x,
		a.y + b.y,
		a.z + b.z
	);
}
Point operator+(const Vector& a, const Point& b) {
	return Point(
		a.x + b.x,
		a.y + b.y,
		a.z + b.z
	);
}
Point operator-(const Point& a, const Vector& b) {
	return Point(
		a.x - b.x,
		a.y - b.y,
		a.z - b.z
	);
}

}