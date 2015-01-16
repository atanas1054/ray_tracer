#include <rt/primmod/bmap.h>
#include <rt/solids/triangle.h>
#include <rt/textures/texture.h>
#include <core/color.h>
#include <iostream>

namespace rt{

	Vector solve(Vector &a, Vector &b, Vector &t){
		Vector k = Vector::rep(0);
		float det = a.x * b.y - a.y * b.x;
		if(det > epsilon || det < -epsilon){
			k.x = (t.x * b.y - t.y * b.x) / det;
			k.y = (t.y * a.x - t.x * a.y) / det;
		}
		return k;
	}

	BumpMapper::BumpMapper(Triangle* base, Texture* bumpmap, const Point& bv1, const Point& bv2, const Point& bv3, float vscale)
		: base(base), bumpmap(bumpmap), bv1(bv1), bv2(bv2), bv3(bv3), vscale(vscale) { 
		//Matrix e = Matrix(Float4(bv1), Float4(bv2), Float4(bv3), Float4(0,0,0,0));
		//Matrix w = Matrix(Float4(base->v1), Float4(base->v2), Float4(base->v3), Float4(0,0,0,0));
		//BumpMapper::transform = product(w, e.invert());

		Vector uv1 = bv2 - bv1;
		Vector uv2 = bv3 - bv1;
		float det = uv1.x * uv2.y - uv2.x * uv1.y;
		if(det < epsilon && det > -epsilon){
			wx = Vector::rep(0);
			wy = Vector::rep(0);
		}else{
			Matrix m = Matrix(
				Float4(uv2.y, -uv1.y, 0, 0),
				Float4(-uv2.x, uv1.x, 0, 0),
				Float4(0, 0, 0, 0),
				Float4(0, 0, 0, 0)
			);
			Matrix e = Matrix(
				Float4(base->v2 - base->v1),
				Float4(base->v3 - base->v1),
				Float4::rep(0),
				Float4::rep(0)
			);
			Matrix w = product(m, e) * (1/det);
			wx = -Vector(w[0][0], w[0][1], w[0][2]);
			wy = -Vector(w[1][0], w[1][1], w[1][2]);
		}

		/*Vector ab = (base->v2 - base->v1);
		Vector ac = (base->v3 - base->v1);

		Vector a = (bv2 - bv1);
		Vector b = (bv3 - bv1);

		Vector factors = solve(a, b, Vector(1, 0, 0));
		wx = -(ab * factors.x + ac * factors.y).normalize();

		factors = solve(a, b,Vector(0, 1, 0));
		wy = -(ab * factors.x + ac * factors.y).normalize();*/
	}

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
			float dx_ = (dx.r + dx.g + dx.b)/3;
			float dy_ = (dy.r + dy.g + dy.b)/3;
      /*
			Vector ex = Vector(1,0,0);
			Vector ey = Vector(0,1,0);
			Vector wx = cross(intsc.normal(), bv2 - bv1).normalize()  * dx_;
			Vector wy = cross(bv2 - bv1, intsc.normal()).normalize() * dy_;
      */
			//std::cout << wx.x << " " << wx.y << " " << wx.z << std::endl;
			return Intersection(intsc.distance, intsc.ray, intsc.solid, (intsc.normal() + wx * dx_ + wy * dy_ ).normalize(), intsc.local());
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