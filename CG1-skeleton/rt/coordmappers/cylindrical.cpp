#include <rt/coordmappers/cylindrical.h>
#include <rt/intersection.h>
#include <core/scalar.h>
#include <rt/solids/solid.h>

namespace rt{

	CylindricalCoordMapper::CylindricalCoordMapper(const Point& origin, const Vector& longitudinalAxis, const Vector& polarAxis)
		: origin(origin)
	{
		Vector c1 = cross(polarAxis, longitudinalAxis);
		pAxis = (lAxis, c1).normalize();
		pMagnitude = polarAxis.length();
		lxp = cross(lAxis, pAxis).normalize();
		lAxis = longitudinalAxis.normalize();
		lMagnitude = longitudinalAxis.length();
	}

    Point CylindricalCoordMapper::getCoords(const Intersection& hit) const
	{
		//
		Point local = hit.local();
		Point o = origin - (hit.solid->getCenter() - Point::rep(0));
		float pDist = (local - o).length() * ( dot( lAxis, (local - o).normalize() ) );
		Point p = o + pDist * lAxis;
		//
		float r = (local - p).length();
		float theta = 0;
		float cos = dot(pAxis, (local - p).normalize());
		//problem with precision
		if(cos < -1){
			cos = -1;
		}
		if(cos > 1){
			cos = 1;
		}
		if(dot(lxp, local - p) > 0){
			theta = -acos(cos);
		}else{
			theta = acos(cos);
		}
		float u = theta / 2 / pi / pMagnitude;
		float v = pDist / lMagnitude;
		return Point(u, v, 0);
	}
}