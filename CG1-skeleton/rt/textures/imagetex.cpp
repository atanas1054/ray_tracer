#include <rt/textures/imagetex.h>
#include <core/image.h>
#include <core/point.h>
#include <math.h>
#include <core/interpolate.h>

namespace rt{


	ImageTexture::ImageTexture()
	{

	}

    ImageTexture::ImageTexture(const Image& image, BorderHandlingType bh, InterpolationType i): image(image), bh(bh), i(i)
	{

	}

    ImageTexture::ImageTexture(const std::string& filename, BorderHandlingType bh, InterpolationType i): bh(bh), i(i)
	{
		image.readPNG(filename);
	}

	RGBColor BilinearInterpolation(float x1, float y1,Image& image)
	{
					float r_,g_,b_;
					Point q1,q2,q3,q4;
						
					q1 = Point((int)x1,(int)y1,0);
					q2 = Point((int)x1+1,(int)y1,0);
					q3 = Point((int)x1,(int)y1+1,0);
					q4 = Point((int)x1+1,(int)y1+1,0);

					r_ = (lerp2d(image(q1.x,q1.y).r,image(q2.x,q2.y).r,image(q3.x,q3.y).r,image(q4.x,q4.y).r,x1-q1.x,y1-q1.y));
					g_ = (lerp2d(image(q1.x,q1.y).g,image(q2.x,q2.y).g,image(q3.x,q3.y).g,image(q4.x,q4.y).g,x1-q1.x,y1-q1.y));
					b_ = (lerp2d(image(q1.x,q1.y).b,image(q2.x,q2.y).b,image(q3.x,q3.y).b,image(q4.x,q4.y).b,x1-q1.x,y1-q1.y));
					return RGBColor(r_,g_,b_);
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
					
					return BilinearInterpolation(x1,y1,image);

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

					return BilinearInterpolation(x1,y1,image);
					

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
					
					return BilinearInterpolation(x1,y1,image);
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