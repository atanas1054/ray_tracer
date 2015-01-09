#ifndef CG1RAYTRACER_GROUPS_MOTIONBLUR_HEADER
#define CG1RAYTRACER_GROUPS_MOTIONBLUR_HEADER

#include <vector>
#include <rt/groups/group.h>
#include <rt/primitive.h>
#include <rt/ray.h>
#include <rt/bbox.h>
#include <core/matrix.h>
namespace rt {

class MotionBlur : public Group {
public:
	Primitive* prim;
	Matrix transformation;
	MotionBlur(){
		transformation = Matrix::identity();
	}
	void rotate(const Vector& axis, float angle);
	void translate(const Vector& t);
    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance) const;
    virtual void rebuildIndex();
    virtual void add(Primitive* p);
	virtual Point getCenter() const;
    virtual void setMaterial(Material* m);
    virtual void setCoordMapper(CoordMapper* cm);
};

}

#endif
