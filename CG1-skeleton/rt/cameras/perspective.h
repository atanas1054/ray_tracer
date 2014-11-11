#ifndef CG1RAYTRACER_CAMERAS_PERSPECTIVE_HEADER
#define CG1RAYTRACER_CAMERAS_PERSPECTIVE_HEADER

#include <rt/cameras/camera.h>
#include <core/vector.h>
#include <core/point.h>
#include <cmath>

namespace rt {

class PerspectiveCamera : public Camera {
public:
	// center: position of eyes
	// forward: relative position of the center of the scene from the eyes
	// up: up direction of the scene
	// verticalOpeningAngle: in phi
	// horizontalOpeningAngle: in phi
    PerspectiveCamera(
        const Point& center,
        const Vector& forward,
        const Vector& up,
        float verticalOpeningAngle,
        float horizonalOpeningAngle
        ) : eyes(center), forward(forward), up(up) {
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
};

}


#endif
