#ifndef CG1RAYTRACER_CSGSOLIDS_CSGSOLID_HEADER
#define CG1RAYTRACER_CSGSOLIDS_CSGSOLID_HEADER

#include <rt/solids/solid.h>
#include <core/point.h>
#include <rt/bbox.h>
#include <vector>

namespace rt {

class CSGSolid : public Solid {

public:
	explicit CSGSolid(CoordMapper* texMapper = nullptr, Material* material = nullptr);
	virtual std::vector<Intersection> intersections(const Ray& ray) const;
};

}


#endif
