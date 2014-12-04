#include <rt/textures/perlin.h>
#include <core/point.h>
#include <core/interpolate.h>
#include <core/scalar.h>
#include <rt/textures/perlin.h>
#include <core/interpolate.h>
#include <cmath>

namespace rt {


namespace {

    /* returns a value in range -1 to 1 */
    float noise(int x, int y, int z) {
        int n = x + y * 57 + z * 997;
        n = (n<<13) ^ n;
        return ( 1.0f - ( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
    }

}

		PerlinTexture::PerlinTexture(const RGBColor& white, const RGBColor& black) : white(white), black(black)
		{
			amplitudeSum = 0;
		}

        void PerlinTexture::addOctave(float amplitude, float frequency)
		{
			amplitudes.push_back(amplitude);
			frequencies.push_back(frequency);
			amplitudeSum += amplitude;
		}

        RGBColor PerlinTexture::getColor(const Point& coord)
		{
			float* val = new float[8];
			Point* xyz = new Point[8];
			xyz[0] = Point(floor(coord.x), floor(coord.y), floor(coord.z));
			xyz[1] = xyz[1] + Vector(1,0,0);
			xyz[2] = xyz[1] + Vector(0,1,0);
			xyz[3] = xyz[1] + Vector(1,1,0);
			xyz[4] = xyz[1] + Vector(0,0,1);
			xyz[5] = xyz[1] + Vector(1,0,1);
			xyz[6] = xyz[1] + Vector(0,1,1);
			xyz[7] = xyz[1] + Vector(1,1,1);

			for(int i = 0; i < amplitudes.size(); i++) {
				float f = frequencies.at(i);
				val += noise((coord.x * f), (coord.y * f), (coord.z * f)) * amplitudes.at(i);
			}

			return lerp3d(
				lerp(white, black, 
			);
		}

        RGBColor PerlinTexture::getColorDX(const Point& coord)
		{
			return RGBColor();
		}

        RGBColor PerlinTexture::getColorDY(const Point& coord)
		{
			return RGBColor();
		}

}
