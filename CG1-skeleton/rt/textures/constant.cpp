#include <rt/textures/constant.h>

namespace rt{

	ConstantTexture::ConstantTexture()
	{

	}

    ConstantTexture::ConstantTexture(const RGBColor& color)
	{

	}

    RGBColor ConstantTexture::getColor(const Point& coord)
	{
		return RGBColor();
	}

    RGBColor ConstantTexture::getColorDX(const Point& coord)
	{
		return RGBColor();
	}

    RGBColor ConstantTexture::getColorDY(const Point& coord)
	{
		return RGBColor();
	}
}