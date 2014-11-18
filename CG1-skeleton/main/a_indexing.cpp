#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>
#include <rt/world.h>
#include <rt/renderer.h>
#include <rt/loaders/obj.h>
#include <rt/groups/bvh.h>
#include <rt/groups/simplegroup.h>
#include <rt/groups/kdtree.h>
#include <rt/solids/sphere.h>
#include <rt/solids/aabox.h>
#include <rt/cameras/perspective.h>
#include <rt/integrators/casting.h>
#include <rt/integrators/castingdist.h>
#include <iostream>
#include <time.h>

using namespace rt;

void a_indexing() {
    Image img(800, 600);

    BVH* scene = new BVH();
	//SimpleGroup* scene = new SimpleGroup();
    scene->add(new Sphere(Point(2.5f,  .5f,  -1), 0.5  , nullptr, nullptr));
    scene->add(new Sphere(Point(2.5f,  -1.f,  -1), 0.5, nullptr, nullptr));
    scene->add(new Sphere(Point(4.5f,  .5f,  -1), 0.5 , nullptr, nullptr));
	
	loadOBJ(scene, "models/", "cow.obj");

	clock_t start = clock();

	scene->rebuildIndex();

	std::cout << ((double) (clock() - start) / CLOCKS_PER_SEC) << "\n";

    World world;
    world.scene = scene;

    PerspectiveCamera cam1(Point(-8.85f, -7.85f, 7.0f), Vector(1.0f,1.0f,-0.6f), Vector(0, 0, 1), pi/8, pi/6);
    PerspectiveCamera cam2(Point(16.065f, -12.506f, 1.771f), Point(-0.286f, -0.107f, 1.35f)-Point(16.065f, -12.506f, 1.771f), Vector(0, 0, 1), pi/8, pi/6);
	RayCastingIntegrator integrator(&world);
    //RayCastingDistIntegrator integrator(&world, RGBColor(1.0f,0.2f,0.0f), 4.0f, RGBColor(0.2f,1.0f,0.0f), 12.0f);

	clock_t start1 = clock();
    Renderer engine1(&cam1, &integrator);
    engine1.render(img);
    img.writePNG("a3-1.png");

    Renderer engine2(&cam2, &integrator);
    engine2.render(img);
    img.writePNG("a3-2.png");
	
	std::cout << ((double) (clock() - start1) / CLOCKS_PER_SEC) << "\n";
	int kkk;
	std::cin >> kkk;


}
