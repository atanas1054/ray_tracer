#include <rt/cameras/perspective.h>
#include <rt/ray.h>

namespace rt {

	Ray PerspectiveCamera::getPrimaryRay(float x, float y) const
	{
		Vector d = forward + x * spanHor + y * spanVer;
		return Ray(
			eyes,
			d.normalize()
		);
	}

}