#include <rt/coordmappers/cylindrical.h>
#include <rt/intersection.h>
#include <core/scalar.h>

namespace rt{

	CylindricalCoordMapper::CylindricalCoordMapper(const Point& origin, const Vector& longitudinalAxis, const Vector& polarAxis)
		: origin(origin), lAxis(longitudinalAxis)
	{
		Vector c1 = cross(polarAxis, lAxis);
		pAxis = (lAxis, c1).normalize();
		pMagnitude = polarAxis.length();
		lxp = cross(lAxis, pAxis).normalize();
	}

    Point CylindricalCoordMapper::getCoords(const Intersection& hit) const
	{
		//projection of hit point to lAxis
		float pDist = (hit.local() - origin).length() * ( dot( lAxis.normalize(), (hit.local() - origin).normalize() ) );
		Point p = origin + pDist * lAxis.normalize();
		//
		float r = (hit.local() - p).length();
		float theta = 0;
		if(dot(lxp, hit.local() - p) > 0){
			theta = -acos(dot(pAxis.normalize(), (hit.local() - p).normalize()));
		}else{
			theta = acos(dot(pAxis.normalize(), (hit.local() - p).normalize()));
		}
		float u = theta / pi / pMagnitude;
		float v = pDist / lAxis.length();
		return Point(u, v, 0);
	}
}