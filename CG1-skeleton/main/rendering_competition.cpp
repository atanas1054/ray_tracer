#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>
#include <rt/world.h>
#include <rt/renderer.h>
#include <rt/loaders/obj.h>
#include <rt/groups/bvh.h>
#include <rt/groups/simplegroup.h>
#include <rt/groups/kdtree.h>
#include <rt/groups/MotionBlur.h>
#include <rt/solids/sphere.h>
#include <rt/solids/quad.h>
#include <rt/solids/aabox.h>
#include <rt/solids/triangle.h>
#include <rt/solids/aabox.h>
#include <rt/primmod/instance.h>
#include <rt/cameras/perspective.h>
#include <rt/integrators/casting.h>
#include <rt/integrators/castingdist.h>
#include <rt/integrators/recraytrace.h>
#include <rt/lights/pointlight.h>
#include <rt/materials/phong.h>
#include <rt/materials/lambertian.h>
#include <rt/materials/mirror.h>
#include <rt/textures/constant.h>
#include <iostream>
#include <time.h>

using namespace rt;



void rendering_competition() {
    Image img(600,400);
	
    BVH* scene = new BVH();
	BVH* sample = new BVH();
	BVH* floor = new BVH();
	BVH* sphere = new BVH();
	MotionBlur* chair = new MotionBlur();
	
	//SimpleGroup* scene = new SimpleGroup();
	//SimpleGroup* scene = new SimpleGroup();
   // scene->add(new Sphere(Point(4,  0,  0.8), 0.5  , nullptr, phong));
	//scene->add(new Sphere(Point(2,  0,  1.8), 0.5  , nullptr, phong));
	//scene->add(new Quad(Point(-10,-10,-1), Vector(20,0,0), Vector(0,20,0), nullptr, lamb));
	//scene->add(new Triangle(Point(-10,-10,-1),Point(-10,10,-1),Point(10,-10,-1),nullptr,lamb));
   // scene->add(new Sphere(Point(2.5f,  -1.f,  -1), 0.5, nullptr, nullptr));
    //scene->add(new Sphere(Point(4.5f,  .5f,  -1), 0.5 , nullptr, nullptr));

	
	loadOBJ(scene, "models/", "room.obj");
	loadOBJ(sample, "models/", "chair.obj");
	loadOBJ(floor, "models/", "floor.obj");
	loadOBJ(sphere, "models/", "sphere.obj");
	sphere->setMaterial(new MirrorMaterial(2.485, 3.433));
	sphere->rebuildIndex();

	floor->rebuildIndex();
	floor->setMaterial(new MirrorMaterial(2.485, 3.433));

	sample->rebuildIndex();

	chair->add(sample);
	chair->translate(-Vector(-0.53539f,-4.56710f,0.11486f));
	chair->rotate(Point(-0.53539f,-4.56710f,0.11486f)-Point(0.22227f,-4.56402f,0.11901f),-pi/6);
	chair->translate(Vector(-0.53539f,-4.56710f,0.11486f));

	Instance* inst1 = new Instance(sample);
	inst1->translate(-Vector(-0.53539f,-4.56710f,0.11486f));
	inst1->rotate(Point(-0.53539f,-4.56710f,0.11486f)-Point(0.22227f,-4.56402f,0.11901f),-pi/6);
	inst1->translate(Vector(-0.53539f,-4.56710f,0.11486f));

	

	scene->add(sphere);
	scene->add(floor);
	scene->add(chair);
	scene->add(inst1);
	

	clock_t start = clock();

	scene->rebuildIndex();

	std::cout << ((double) (clock() - start) / CLOCKS_PER_SEC) << "\n";

    World world;
    world.scene = scene;
	//scene->add(new Sphere(Point(0,  0,  0), 2 , nullptr, nullptr));

	world.light.push_back(new PointLight(Point(5.20312f,-1.55587f, 2.11942f),RGBColor::rep(150000.0f*0.04f*0.04f)));
	world.light.push_back(new PointLight(Point(0.83065f,-2.16278f, 6.16367f),RGBColor::rep(150000.0f*0.02f*0.02f)));
	PerspectiveCamera cam1(Point(2.16113f, -9.22764f, 2.72367f), Vector(-0.31158f,0.876665f, -0.36724f), Vector(-0.0414f,0.3738f,0.9265f), pi/4, pi/4);
    PerspectiveCamera cam2(Point(16.065f, -12.506f, 1.771f), Point(-0.286f, -0.107f, 1.35f)-Point(16.065f, -12.506f, 1.771f), Vector(0, 0, 1), pi/8, pi/6);
	RecursiveRayTracingIntegrator integrator(&world);
	//RayCastingIntegrator integrator(&world);
    //RayCastingDistIntegrator integrator(&world, RGBColor(1.0f,0.2f,0.0f), 4.0f, RGBColor(0.2f,1.0f,0.0f), 12.0f);
	
	clock_t start1 = clock();
    Renderer engine1(&cam1, &integrator);
	engine1.setSamples(1);
	engine1.render(img);
    img.writePNG("room1.png");

    Renderer engine2(&cam2, &integrator);
    engine2.render(img);
    img.writePNG("room2.png");
	
	std::cout << ((double) (clock() - start1) / CLOCKS_PER_SEC) << "\n";
	int kkk;
	std::cin >> kkk;


}
