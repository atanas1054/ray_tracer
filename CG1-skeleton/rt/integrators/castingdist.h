#ifndef CG1RAYTRACER_INTEGRATORS_CASTINGDIST_HEADER
#define CG1RAYTRACER_INTEGRATORS_CASTINGDIST_HEADER

#include <rt/integrators/integrator.h>
#include <core/color.h>

namespace rt {

class World;
class Ray;

class RayCastingDistIntegrator : public Integrator {
public:
	float lenR;
	float lenG;
	float lenB;
	RGBColor nearColor;
	float nearDist;
	float lenDist;
public:
    RayCastingDistIntegrator(World* world, const RGBColor& nearColor, float nearDist, const RGBColor& farColor, float farDist);
    virtual RGBColor getRadiance(const Ray& ray) const;
};

}

#endif
