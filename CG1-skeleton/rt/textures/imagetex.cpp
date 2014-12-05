#include <rt/textures/imagetex.h>
#include <core/image.h>
#include <core/point.h>
#include <math.h>
#include <core/interpolate.h>

namespace rt{


	ImageTexture::ImageTexture()
	{
		bh = REPEAT;
		i = BILINEAR;
	}

    ImageTexture::ImageTexture(const Image& image, BorderHandlingType bh, InterpolationType i): image(image), bh(bh), i(i)
	{

	}

    ImageTexture::ImageTexture(const std::string& filename, BorderHandlingType bh, InterpolationType i): bh(bh), i(i)
	{
		image.readPNG(filename);
	}

	RGBColor BilinearInterpolation(float x1, float y1,Image& image, ImageTexture::BorderHandlingType bh)
	{
		float r_,g_,b_;
		Point q1,q2,q3,q4;
		
		int px0, px1, py0, py1;
		px0 = (int) floor(x1);
		py0 = (int) floor(y1);
		px1 = px0 + 1;
		py1 = py0 + 1;
		if(bh == ImageTexture::REPEAT)
		{
			px1 = px1 % (int)image.width();
			py1 = py1 % (int)image.height();
		} else {
			if(px1 == image.width()) px1 = image.width() - 1;
			if(py1 == image.height()) py1 = image.height() - 1;
		}

		return lerp2d(image(px0, py0), image(px1, py0), image(px0, py1), image(px1, py1), x1 - px0, y1 - py0);
	}

    RGBColor ImageTexture::getColor(const Point& coord)
	{
		if (i==NEAREST)
		{
			switch(bh)
			{
				float x1,y1;
				case REPEAT:
					x1 = coord.x;
					y1 = coord.y;
					if(coord.x>1)
						x1 = coord.x - (int)coord.x;
					if(coord.y>1)
						y1 = coord.y - (int)coord.y;
					if(coord.x<0)
						x1 = coord.x - floor(coord.x);
					if(coord.y<0)
						y1 = coord.y - floor(coord.y);
					x1 = x1*(image.width()-1);
					y1 = y1*(image.height()-1);
					return RGBColor(image(floor(x1+0.5),floor(y1+0.5)));

				case MIRROR:
					x1 = coord.x;
					y1 = coord.y;
					if((int)(floor(coord.x))%2==0)
						x1 = coord.x - floor(coord.x);
					else
						x1 = 1 - (coord.x - floor(coord.x));

					if((int)(floor(coord.y))%2==0)
						y1 = coord.y - floor(coord.y);
					else
						y1 = 1 - (coord.y - floor(coord.y));
					x1 = x1*(image.width()-1);
					y1 = y1*(image.height()-1);
					return RGBColor(image(floor(x1+0.5),floor(y1+0.5)));
					

				case CLAMP:
					x1 = coord.x;
					y1 = coord.y;
					if(coord.x>1)
						x1 = 1;
					if(coord.y>1)
						y1 = 1;
					if(coord.x<0)
						x1 = 0;
					if(coord.y<0)
						y1 = 0;
					x1 = x1*(image.width()-1);
					y1 = y1*(image.height()-1);
					return RGBColor(image(floor(x1+0.5),floor(y1+0.5)));

			}
		}

		if (i==BILINEAR)
		{
			Point q1,q2,q3,q4;
			float x1,y1,r_,g_,b_;
			switch(bh)
			{
				
				case REPEAT:
					
					x1 = coord.x;
					y1 = coord.y;
					if(coord.x>1)
						x1 = coord.x - (int)coord.x;
					if(coord.y>1)
						y1 = coord.y - (int)coord.y;
					if(coord.x<0)
						x1 = coord.x - floor(coord.x);
					if(coord.y<0)
						y1 = coord.y - floor(coord.y);
					x1 = x1*(image.width()-1);
					y1 = y1*(image.height()-1);

					return BilinearInterpolation(x1,y1,image, bh);

					case MIRROR:
					x1 = coord.x;
					y1 = coord.y;
					if((int)(floor(coord.x))%2==0)
						x1 = coord.x - floor(coord.x);
					else
						x1 = 1 - (coord.x - floor(coord.x));

					if((int)(floor(coord.y))%2==0)
						y1 = coord.y - floor(coord.y);
					else
						y1 = 1 - (coord.y - floor(coord.y));

					x1 = x1*(image.width()-1);
					y1 = y1*(image.height()-1);

					return BilinearInterpolation(x1,y1,image, bh);
					

				case CLAMP:
					x1 = coord.x;
					y1 = coord.y;
					if(coord.x>1)
						x1 = 1;
					if(coord.y>1)
						y1 = 1;
					if(coord.x<0)
						x1 = 0;
					if(coord.y<0)
						y1 = 0;
					x1 = x1*(image.width()-1);
					y1 = y1*(image.height()-1);
					
					return BilinearInterpolation(x1,y1,image, bh);
			}
		}

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