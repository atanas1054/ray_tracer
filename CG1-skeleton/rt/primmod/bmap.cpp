#include <rt/primmod/bmap.h>
#include <rt/solids/triangle.h>


namespace rt{

	BumpMapper::BumpMapper(Triangle* base, Texture* bumpmap, const Point& bv1, const Point& bv2, const Point& bv3, float vscale)
	{

	}

	BBox BumpMapper::getBounds() const
	{
		return BBox();
	}

    Intersection BumpMapper::intersect(const Ray& ray, float previousBestDistance) const
	{
		return Intersection();
	}

    void BumpMapper::setMaterial(Material* m)
	{

	}

    void BumpMapper::setCoordMapper(CoordMapper* cm)
	{

	}

	Point BumpMapper::getCenter() const
	{
		return Point();
	}
}