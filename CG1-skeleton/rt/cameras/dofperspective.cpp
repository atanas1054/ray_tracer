#include <rt/cameras/dofperspective.h>
#include <rt/ray.h>
#include <core/random.h>
#include <cmath>
#include <core/scalar.h>

namespace rt 
{
    Ray DOFPerspectiveCamera::getPrimaryRay(float x, float y) const
	{	
		Vector d = forward + x * spanHor + y * spanVer;
		Ray focalRay(eyes,d.normalize());
		Point focalPoint = focalRay.getPoint(focal);
		//Point newOrigin = eyes + (random() - 0.5)*radius*spanHor/spanHor.length() + (random() - 0.5)*radius*spanVer/spanVer.length();
		//using polar coordinates
		float u = random();
		float v = std::sqrt(random());
		float theta = u * 2 * pi;
		float dx = std::cos(theta) * v;
		float dy = std::sin(theta) * v;
		Point newOrigin = eyes + dx*radius*spanHor / spanHor.length() + dy*radius*spanVer / spanVer.length();
		return Ray(newOrigin,(focalPoint-newOrigin).normalize());
	}
}