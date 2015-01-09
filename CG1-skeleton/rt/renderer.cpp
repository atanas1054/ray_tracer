#include <rt/renderer.h>
#include <core/image.h>
#include <rt/cameras/camera.h>
#include <core/point.h>
#include <core/julia.h>
#include <core/vector.h>
#include <rt/ray.h>
#include <rt/integrators/integrator.h>
#include <core/random.h>

namespace rt {

	float a1computeWeight(float fx, float fy, const Point& c, float div) {
		Point v(fx, fy, 0.5f);
		v = v - Vector::rep(0.5f);
		v = v * 2.0f;
		int numIter = julia(v, c);
		return numIter/(numIter+div);
	}

	RGBColor a1computeColor(uint x, uint y, uint width, uint height) {
		float fx =  float(x) / float(width);
		float fy =  float(y) / float(height);
		RGBColor color = RGBColor::rep(0.0f);
		color = color + a1computeWeight(fx, fy, Point(-0.8f, 0.156f, 0.0f), 64.0f) * RGBColor(0.8f, 0.8f, 1.0f);
		color = color + a1computeWeight(fx, fy, Point(-0.6f, 0.2f, 0.0f), 64.0f)*0.2f * RGBColor(0.5f, 0.5f, -0.2f);
		color = color + a1computeWeight(fy, fx, Point(0.285f, 0.0f, 0.0f), 64.0f) * RGBColor(0.2f, 0.3f, 0.4f);
		return RGBColor::rep(1.0f) - color;
	}

	float a2computeWeight(float fx, float fy, const Point& c, float div) {
		Point v(fx, fy, 0.0f);
		int numIter = julia(v, c);
		return numIter/(numIter+div);
	}

	RGBColor a2computeColor(const Ray& r) {
		float theta = asin(r.d.z)/pi*2;
		float phi = atan2(r.d.y,r.d.x)/pi;
		float ofx = absfractional((r.o.x+1.0f)/2.0f)*2.0f-1.0f;
		float ofy = absfractional((r.o.y+1.0f)/2.0f)*2.0f-1.0f;
		RGBColor color = RGBColor::rep(0.0f);
		color = color + a2computeWeight(phi, theta, Point(-0.8f, 0.156f, 0.0f), 64.0f) * RGBColor(0.8f, 0.8f, 1.0f);
		color = color + a2computeWeight(phi, theta, Point(-0.6f, 0.2f, 0.0f), 64.0f)*0.2f * RGBColor(0.5f, 0.5f, -0.2f);
		color = color + a2computeWeight(ofy, ofx, Point(0.285f, 0.0f, 0.0f), 64.0f) * RGBColor(0.4f, 0.5f, 0.6f);
		color = RGBColor::rep(1.0f) - color;
		if (absfractional(theta/(2*pi)*90)<0.03) color = RGBColor(0.9f,0.5f,0.5f)*0.7f;
		if (absfractional(phi/(2*pi)*90)<0.03) color = RGBColor(0.9f,0.9f,0.5f)*0.7f;
		return color;
	}

	Renderer::Renderer(Camera* cam, Integrator* integrator):  camera(cam), integrator(integrator) {
		samples = 1;
	}
	void Renderer::setSamples(uint samples) {
		Renderer::samples = samples;
	}

	void Renderer::render(Image& img) {
		Ray ray;
		if (samples > 1) {
			Vector c;
			RGBColor pixel;
			//#pragma omp parallel for private(ray) schedule (dynamic,1)
			for(int i = 0; i < img.width();i++){
				for(int j = 0; j < img.height();j++){
					//if(i == 284 && j == 129){
						//i = i;
					//}
					//c = Vector(2 * (i + 0.5) / img.width() - 1, 2 * (j + 0.5) / img.height() - 1, 0);
					pixel = RGBColor::rep(0);
					for(int k = 0; k < samples; k++) {
						ray = (*(Renderer::camera)).getPrimaryRay(
							//c.x + (random() - 0.5) / img.width(),
							//c.y + (random() - 0.5) / img.height()
							2 * (i + random()) / img.width() - 1,
							2 * (j + random()) / img.height() - 1
							//c.x, c.y
						);
						pixel = pixel + (*(Renderer::integrator)).getRadiance(ray);
					}
					pixel = pixel / samples;
					img(i, j) = pixel;
				}
			}
		} else {
			#pragma omp parallel for private(ray) schedule (dynamic,1)
			for(int i = 0; i < img.width();i++){
				for(int j = 0; j < img.height();j++){
					ray = (*(Renderer::camera)).getPrimaryRay(
						2 * (i + 0.5) / img.width() - 1,
						2 * (j + 0.5) / img.height() - 1
					);
					//if(i == 259 && j == 290){
						//i = i;
					//}
					img(i, j) = (*(Renderer::integrator)).getRadiance(ray);
				}
			}
		}
	}
	void Renderer::test_render1(Image& img) {
		for(int i = 0; i < img.width();i++){
			for(int j = 0; j < img.height();j++){
				img(i, j) = a1computeColor(i , j, img.width(), img.height());
			}
		}
	}
	void Renderer::test_render2(Image& img) {
		for(int i = 0; i < img.width();i++){
			for(int j = 0; j < img.height();j++){
				img(i, j) = a2computeColor((*(Renderer::camera)).getPrimaryRay(
					2 * (i + 0.5) / img.width() - 1,
					2 * (j + 0.5) / img.height() - 1
				));
			}
		}
	}

}