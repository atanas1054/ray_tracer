#include <rt/ray.h>

namespace rt {

	Ray::Ray(const Point& o, const Vector& d): o(o), d(d) {
		Ray::d.normalize();
	}
	Point Ray::getPoint(float distance) const {
		return o + ((d * distance) / d.length());
	}

}