#include <core/point.h>
#include <core/vector.h>
#include <core/float4.h>

namespace rt{

Point::Point(const Float4& f4)
{
	x = f4.x;
	y = f4.y;
	z = f4.z;
}

Vector Point::operator-(const Point& b) const {
	return Vector(x - b.x, y - b.y, z - b.z);
}

bool Point::operator==(const Point& b) const {
	return x == b.x && y == b.y && z == b.z;
}

bool Point::operator!=(const Point& b) const {
	return x != b.x && y != b.y && z != b.z;
}

Point operator*(float scalar, const Point& b) {
	return Point(scalar * b.x, scalar * b.y, scalar * b.z);
}

Point operator*(const Point& a, float scalar) {
	return Point(scalar * a.x, scalar * a.y, scalar * a.z);
}

Point min(const Point& a, const Point& b) {
	return Point(
		a.x < b.x?a.x:b.x,
		a.y < b.y?a.y:b.y,
		a.z < b.z?a.z:b.z
	);
}

Point max(const Point& a, const Point& b) {
	return Point(
		a.x > b.x?a.x:b.x,
		a.y > b.y?a.y:b.y,
		a.z > b.z?a.z:b.z
	);
}

}