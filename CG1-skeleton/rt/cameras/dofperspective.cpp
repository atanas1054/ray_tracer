#include <rt/cameras/dofperspective.h>
#include <rt/ray.h>
#include <core/random.h>

namespace rt 
{
    Ray DOFPerspectiveCamera::getPrimaryRay(float x, float y) const
	{	
		Vector d = forward + x * spanHor + y * spanVer;
		Ray focalRay(eyes,d.normalize());
		Point focalPoint = focalRay.getPoint(focal);
		Point newOrigin = eyes + (random() - 0.5)*radius*spanHor/spanHor.length() + (random() - 0.5)*radius*spanVer/spanVer.length();
		return Ray(newOrigin,(focalPoint-newOrigin).normalize());
	}
}