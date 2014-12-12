#ifndef CG1RAYTRACER_CSGSOLIDS_CSGSPHERE_HEADER
#define CG1RAYTRACER_CSGSOLIDS_CSGSPHERE_HEADER

//#include <rt/groups/csgsolids/csgsolid.h>
#include <rt/groups/csg.h>
#include <core/point.h>
#include <rt/bbox.h>

namespace rt {

class CSGSphere : public CSG {

public:
	float radius;
	Point center;

    CSGSphere() : CSG(CombineType::UNION, nullptr, nullptr) {}
    CSGSphere(const Point& center, float radius, CoordMapper* texMapper, Material* material);

	virtual Point getCenter() const;
    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
	virtual std::vector<Intersection*> intersections(const Ray& ray) const;
	virtual Point sample() const;
    virtual float getArea() const;
};

}


#endif
