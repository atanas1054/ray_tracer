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

	float interpolatedNoise(float x, float y, float z)
	{
		int x0 = (int) floor(x);
		int x1 = x0 + 1;
		int y0 = (int) floor(y);
		int y1 = y0 + 1;
		int z0 = (int) floor(z);
		int z1 = z0 + 1;
		float* n = new float[8];
		n[0] = noise(x0, y0, z0);
		n[1] = noise(x1, y0, z0);
		n[2] = noise(x0, y1, z0);
		n[3] = noise(x1, y1, z0);
		n[4] = noise(x0, y0, z1);
		n[5] = noise(x1, y0, z1);
		n[6] = noise(x0, y1, z1);
		n[7] = noise(x1, y1, z1);
		return lerp3d(n[0], n[1], n[2], n[3], n[4], n[5], n[6], n[7], x - x0, y - y0, z - z0);
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
			float val = 0;
			float f,a;
			for(int i = 0; i < amplitudes.size(); i++) {
				f = frequencies.at(i);
				a = amplitudes.at(i);
				val += interpolatedNoise(coord.x * f, coord.y * f, coord.z * f) * a;
			}
			return lerp(black, white, (val / amplitudeSum + 1)/ 2);
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
