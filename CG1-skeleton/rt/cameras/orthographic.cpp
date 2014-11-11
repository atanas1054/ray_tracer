#include <rt/cameras/orthographic.h>
#include <rt/ray.h>

namespace rt {

	OrthographicCamera::OrthographicCamera(
        const Point& center,
        const Vector& forward,
        const Vector& up,
        float scaleX,
        float scaleY
		) : center(center), forward(forward), up(up) {
			Vector crossVec = cross(forward, up);
			spanX = crossVec / crossVec.length() * scaleX / 2;
			crossVec = cross(forward, spanX);
			spanY = crossVec / crossVec.length() * scaleY / 2;
			d = cross(spanX, spanY);
			d = d / d.length();
	}

	Ray OrthographicCamera::getPrimaryRay(float x, float y) const
	{
		
		return Ray(center + x * spanX + y * spanY, d);
	}
}