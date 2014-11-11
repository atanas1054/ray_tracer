#ifndef CG1RAYTRACER_CAMERAS_CAMERA_HEADER
#define CG1RAYTRACER_CAMERAS_CAMERA_HEADER

namespace rt {

class Ray;

class Camera {
public:
	Camera(){ }
	//x and y is [-1, 1]
    virtual Ray getPrimaryRay(float x, float y) const = 0;
};

}

#endif

