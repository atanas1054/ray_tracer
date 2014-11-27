#include <core/color.h>
#include <cmath>

namespace rt {

RGBColor RGBColor::operator+(const RGBColor& c) const {
	float tempR = r + c.r;
	float tempG = g + c.g;
	float tempB = b + c.b;
	return RGBColor(
		tempR > 1 ? 1 : tempR,
		tempG > 1 ? 1 : tempG,
		tempB > 1 ? 1 : tempB
	);
}
RGBColor RGBColor::operator-(const RGBColor& c) const {
	float tempR = r - c.r;
	float tempB = b - c.b;
	float tempG = g - c.g;
	return RGBColor(
		tempR < 0 ? 0 : tempR,
		tempG < 0 ? 0 : tempG,
		tempB < 0 ? 0 : tempB
	);
	//return RGBColor(r - c.r, b - c.b, g - c.g);
}
RGBColor RGBColor::operator*(const RGBColor& c) const {
	return RGBColor(r * c.r, g * c.g, b * c.b);
}
bool RGBColor::operator==(const RGBColor& b) const {
	return r == b.r && g == b.g && RGBColor::b == b.b;
}
bool RGBColor::operator!=(const RGBColor& b) const {
	return r != b.r && g != b.g && RGBColor::b != b.b;
}
RGBColor RGBColor::clamp() const {
	return RGBColor(
		r > 1 ? 1 : (r < 0 ? 0 : r),
		g > 1 ? 1 : (g < 0 ? 0 : g),
		b > 1 ? 1 : (b < 0 ? 0 : b)
	);
}

RGBColor operator*(float scalar, const RGBColor& b) {
	float tempR = scalar * b.r;
	float tempG = scalar * b.g;
	float tempB = scalar * b.b;
	return RGBColor(
		tempR,
		tempG,
		tempB
		//tempR > 1 ? 1 : tempR,
		//tempG > 1 ? 1 : tempG,
		//tempB > 1 ? 1 : tempB
	);
}
RGBColor operator*(const RGBColor& a, float scalar) {
	float tempR = scalar * a.r;
	float tempG = scalar * a.g;
	float tempB = scalar * a.b;
	return RGBColor(
		tempR,
		tempG,
		tempB
		/*tempR > 1 ? 1 : tempR,
		tempG > 1 ? 1 : tempG,
		tempB > 1 ? 1 : tempB*/
	);
}
RGBColor operator/(const RGBColor& a, float scalar) {
	float tempR = a.r / scalar;
	float tempG = a.g / scalar;
	float tempB = a.b / scalar;
	return RGBColor(
		tempR,tempG,tempB
		/*tempR > 1 ? 1 : tempR,
		tempG > 1 ? 1 : tempG,
		tempB > 1 ? 1 : tempB*/
	);
}

}