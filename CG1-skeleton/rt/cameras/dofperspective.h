#ifndef CG1RAYTRACER_CAMERAS_DOFPERSPECTIVE_HEADER
#define CG1RAYTRACER_CAMERAS_DOFPERSPECTIVE_HEADER

#include <rt/cameras/camera.h>
#include <core/vector.h>
#include <core/point.h>
#include <cmath>

namespace rt {

class DOFPerspectiveCamera : public Camera {
public:
    DOFPerspectiveCamera(
        const Point& center,
        const Vector& forward,
        const Vector& up,
        float verticalOpeningAngle,
        float horizonalOpeningAngle,
        float focalDistance,
        float apertureRadius
        ): eyes(center), forward(forward), up(up), focal(focalDistance),radius(apertureRadius) {
		Vector crossVec = cross(forward, up);
		spanHor = crossVec / crossVec.length() * std::tan(horizonalOpeningAngle / 2) * forward.length();
		crossVec = cross(forward, spanHor);
		spanVer = crossVec / crossVec.length() * std::tan(verticalOpeningAngle / 2) * forward.length();
	}

    virtual Ray getPrimaryRay(float x, float y) const;
	public:
	Point eyes;
	Vector forward;
	Vector up;
	Vector spanVer;
	Vector spanHor;
	float focal, radius;
};

}


#endif
