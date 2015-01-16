#include <core/color.h>
#include <cmath>

namespace rt {

RGBColor RGBColor::operator+(const RGBColor& c) const {
	return RGBColor(
		r + c.r,
		g + c.g,
		b + c.b
	);
}
RGBColor RGBColor::operator-(const RGBColor& c) const {
	float tempR = r - c.r;
	float tempB = b - c.b;
	float tempG = g - c.g;
	
	return RGBColor(r - c.r, b - c.b, g - c.g);
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
	return RGBColor(
		scalar * b.r,
		scalar * b.g,
		scalar * b.b
	);
}
RGBColor operator*(const RGBColor& a, float scalar) {
	return RGBColor(
		scalar * a.r,
		scalar * a.g,
		scalar * a.b
	);
}
RGBColor operator/(const RGBColor& a, float scalar) {
	return RGBColor(
		a.r / scalar,
		a.g / scalar,
		a.b / scalar
	);
}

}