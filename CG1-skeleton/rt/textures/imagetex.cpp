#include <rt/textures/imagetex.h>

namespace rt{


	ImageTexture::ImageTexture()
	{

	}

    ImageTexture::ImageTexture(const Image& image, BorderHandlingType bh, InterpolationType i)
	{

	}

    ImageTexture::ImageTexture(const std::string& filename, BorderHandlingType bh, InterpolationType i)
	{

	}

    RGBColor ImageTexture::getColor(const Point& coord)
	{
		return RGBColor();
	}

    RGBColor ImageTexture::getColorDX(const Point& coord)
	{
		return RGBColor();
	}

    RGBColor ImageTexture::getColorDY(const Point& coord)
	{
		return RGBColor();
	}
}