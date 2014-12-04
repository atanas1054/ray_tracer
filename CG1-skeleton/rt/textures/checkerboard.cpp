#include <rt/textures/checkerboard.h>
#include <core/point.h>
#include <cmath>

namespace rt{

	 CheckerboardTexture::CheckerboardTexture(const RGBColor& white, const RGBColor& black): white(white), black(black)
	 {

	 }

	 int compute1(float y)
	 {
		 float z = y * 2;
		 if(z > 0)
			return (int)z;
		 return (int)(z - 1) ;
	 }

	 RGBColor CheckerboardTexture::getColor(const Point& coord)
	 {
		 int x = compute1(coord.x);
		 int y = compute1(coord.y);
		 int z = compute1(coord.z);

		 if(( x + y + z) % 2 == 0)
		 {
			 return white;
		 }
		 return black;
	 }

     RGBColor CheckerboardTexture::getColorDX(const Point& coord)
	 {
		 return RGBColor();
	 }

	 RGBColor CheckerboardTexture::getColorDY(const Point& coord)
	 {
		 return RGBColor();
	 }
}