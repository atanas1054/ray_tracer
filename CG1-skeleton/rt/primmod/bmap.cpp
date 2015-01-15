#include <rt/primmod/bmap.h>
#include <rt/solids/triangle.h>
#include <rt/textures/texture.h>
#include <core/color.h>
#include <core/matrix.h>

namespace rt{

	BumpMapper::BumpMapper(Triangle* base, Texture* bumpmap, const Point& bv1, const Point& bv2, const Point& bv3, float vscale)
		: base(base), bumpmap(bumpmap), bv1(bv1), bv2(bv2), bv3(bv3), vscale(vscale) { }

	BBox BumpMapper::getBounds() const
	{
		return base->getBounds();
	}

    Intersection BumpMapper::intersect(const Ray& ray, float previousBestDistance) const
	{
		Intersection intsc = base->intersect(ray, previousBestDistance);
		if(intsc){
			Point bary = intsc.local();
			Point uvw = Point(
				bv1.x * bary.x + bv2.x * bary.y + bv3.x * bary.z,
				bv1.y * bary.x + bv2.y * bary.y + bv3.y * bary.z,
				bv1.z * bary.x + bv2.z * bary.y + bv3.z * bary.z
			);
			RGBColor dx = bumpmap->getColorDX(uvw);
			RGBColor dy = bumpmap->getColorDY(uvw);
			float dx_ = (dx.r + dx.g + dx.b) / 3;
			float dy_ = (dy.r + dy.g + dy.b) / 3;
			Matrix m1 = 
			Vector ex = Vector(1,0,0);
			Vector ey = Vector(0,1,0);
			Vector wx = cross(intsc.normal(), bv2 - bv1).normalize()  * dx_;
			Vector wy = cross(bv2 - bv1, intsc.normal()).normalize() * dy_;
			return Intersection(intsc.distance, intsc.ray, intsc.solid, (intsc.normal() + wx + wy).normalize(), intsc.local());
		}
		return intsc;
	}

    void BumpMapper::setMaterial(Material* m)
	{
		base->setMaterial(m);
	}

    void BumpMapper::setCoordMapper(CoordMapper* cm)
	{
		base->setCoordMapper(cm);
	}

	Point BumpMapper::getCenter() const
	{
		return base->getCenter();
	}
}