#ifndef CG1RAYTRACER_CSGSOLID_CSGBOX_HEADER
#define CG1RAYTRACER_CSGSOLIDS_CSGBOX_HEADER

#include <rt/groups/csg.h>
#include <rt/bbox.h>

namespace rt {

class CSGAABox : public CSG {
public:
	Point corner1, corner2;
	CSGAABox() : CSG(CSG::CombineType::UNION, nullptr, nullptr) { }
    CSGAABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material);

    virtual BBox getBounds() const;
	virtual Point getCenter() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
	virtual std::vector<Intersection*> intersections(const Ray& ray) const;
    virtual Point sample() const;
    virtual float getArea() const;
};

}

#endif
