#include <rt/cameras/dofperspective.h>
#include <rt/ray.h>

namespace rt 
{
	DOFPerspectiveCamera::DOFPerspectiveCamera(
        const Point& center,
        const Vector& forward,
        const Vector& up,
        float verticalOpeningAngle,
        float horizonalOpeningAngle,
        float focalDistance,
        float apertureRadius
		):
			center(center), forward(forward), up(up), vAngle(verticalOpeningAngle),
			hAngle(horizonalOpeningAngle), focal(focalDistance), radius(apertureRadius)
	{ }

    Ray DOFPerspectiveCamera::getPrimaryRay(float x, float y) const
	{
		return Ray();
	}
}